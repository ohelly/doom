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
				printf("Player collided with wall\n");
				return (0);
			}
		}
		n++;
	}
	return (1);
}

//returns 0 if quad pl1-pl2 intersected with obj collider
int		obj_collision(t_doom *doom, t_xy pl1, t_xy pl2)
{
	int		n;
	t_xy	pos1;
	t_xy	pos2;

	n = 0;
	while (n < doom->numobjs)
	{
		if (doom->obj[n].col_passable)
		{
			n++;
			continue ;
		}
		pos1 = v2_addf(doom->obj[n].p, -doom->obj[n].col_size);
		pos2 = v2_addf(doom->obj[n].p, doom->obj[n].col_size);
		//if (intersects_collider(pl1, pl2, pos1, pos2))
		if (IntersectBox(pl1.x, pl1.y, pl2.x, pl2.y, pos1.x, pos1.y, pos2.x, pos2.y))
		{
			printf("Player collided with obj\n");
			return (0);
		}
		
		n++;
	}
	return (1);
}

int		player_move(t_doom *doom, t_xy delta)
{
	t_xy		player;
	t_xy		pl1;
	t_xy		pl2;

	player = (t_xy){doom->player.where.x, doom->player.where.y};
	player = v2_add(player, delta);
	pl1 = v2_addf(player, -doom->player.col_size);
	pl2 = v2_addf(player, doom->player.col_size);

	if (!walls_collision(doom, pl1, pl2) || !obj_collision(doom, pl1, pl2))
		return (0);

	//delta.x *= walls_collision(doom, pl1, pl2, (t_xy){delta.x, 0});
	//delta.y *= walls_collision(doom, pl1, pl2, (t_xy){0, delta.y});
	//delta.x *= obj_collision (doom, pl1, pl2, (t_xy){delta.x, 0});
	//delta.y *= obj_collision (doom, pl1, pl2, (t_xy){0, delta.y});

	doom->player.where.x = player.x;
	doom->player.where.y = player.y;
	doom->player.anglesin = sinf(doom->player.angle);
	doom->player.anglecos = cosf(doom->player.angle);
	return (1);
}
