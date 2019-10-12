#include "doom.h"

//returns 0 if quad pl1-pl2 intersects with a wall
int		walls_collision(t_doom *doom, t_xy pl1, t_xy pl2)
{
	t_sector	*sect;
	t_xy		*v;
	int			n;
	t_xy		pos1;
	t_xy		pos2;
	t_xy		hole;
	t_xy		move_pos;

	sect = &doom->sector[doom->player.sector];
	v = sect->vert;
	n = 0;
	while (n < sect->npoints)
	{
		pos1 = v2_addf(v[n], doom->wall_col_size);
		pos2 = v2_addf(v[n + 1], -doom->wall_col_size);
		if (IntersectBox(pl1.x, pl1.y, pl2.x, pl2.y, pos1.x, pos1.y, pos2.x, pos2.y))
		{
			hole.x = sect->neighbors[n] < 0 ?  9e9 : max(sect->floor, doom->sector[sect->neighbors[n]].floor);
			hole.y = sect->neighbors[n] < 0 ? -9e9 : min(sect->ceil,  doom->sector[sect->neighbors[n]].ceil);
			if (hole.y < doom->player.where.z + HeadMargin ||
				hole.x > doom->player.where.z - EyeHeight + KneeHeight)
			{
				//printf("Player collided with wall\n");
				return (0);
			}
		}
		n++;
	}
	return (1);
}

//returns 0 if quad pl1-pl2 intersected with obj collider
int		obj_collision(t_doom *doom, t_xy player)
{
	int		n;
	t_obj	obj;

	n = 0;
	while (n < doom->numobjs)
	{
		obj = doom->obj[n];
		if (obj.col_passable || !obj.enabled)
		{
			n++;
			continue ;
		}
		if (collision_circle(player, doom->player.col_size, obj.p, obj.col_size))
		{
			//printf("Player collided with obj\n");
			return (0);
		}
		
		n++;
	}
	return (1);
}

int		player_move(t_doom *doom, t_xy delta)
{
	t_xy		player;
	t_xy		move_pos;
	t_xy		pl1;
	t_xy		pl2;

	player = (t_xy){doom->player.where.x, doom->player.where.y};

	move_pos = v2_add(player, (t_xy){delta.x, 0});
	pl1 = v2_addf(move_pos, -doom->player.col_size);
	pl2 = v2_addf(move_pos, doom->player.col_size);
	delta.x *= walls_collision(doom, pl1, pl2);

	move_pos = v2_add(player, (t_xy){0, delta.y});
	pl1 = v2_addf(move_pos, -doom->player.col_size);
	pl2 = v2_addf(move_pos, doom->player.col_size);
	delta.y *= walls_collision(doom, pl1, pl2);

	move_pos = v2_add(player, (t_xy){delta.x, 0});
	delta.x *= obj_collision(doom, move_pos);

	move_pos = v2_add(player, (t_xy){0, delta.y});
	delta.y *= obj_collision(doom, move_pos);

	doom->player.where.x = player.x + delta.x;
	doom->player.where.y = player.y + delta.y;
	doom->player.anglesin = sinf(doom->player.angle);
	doom->player.anglecos = cosf(doom->player.angle);
	return (1);
}

//returns 1 if found interactable obj in closest proximity
int		find_obj_interaction(t_doom *doom)
{
	int		n;
	t_obj	obj;
	t_xy	p;
	t_xy	d;

	p = (t_xy){doom->player.where.x, doom->player.where.y};
	d = (t_xy){doom->player.anglecos * 4, doom->player.anglesin * 4};

	n = 0;
	while (n < doom->numobjs)
	{
		obj = doom->obj[n];
		if (!obj.enabled || obj.on_interaction == NULL)
		{
			n++;
			continue ;
		}
		if (collision_box(p, v2_add(p, d), v2_addf(obj.p, -obj.col_size), v2_addf(obj.p, obj.col_size)))
		{
			obj.on_interaction(doom, &obj);
			printf("Player interacted with obj %d\n", obj.id);
			printf("Positions are p %f:%f, pd %f:%f, pos1 %f:%f, pos2 %f:%f\n", p.x, p.y, v2_add(p, d).x, v2_add(p, d).y, v2_addf(obj.p, -obj.col_size).x, v2_addf(obj.p, -obj.col_size).y, v2_addf(obj.p, obj.col_size).x, v2_addf(obj.p, obj.col_size).y);
			return (1);
		}
		n++;
	}
	return (0);
}
