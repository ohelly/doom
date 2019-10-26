/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:24:41 by njacobso          #+#    #+#             */
/*   Updated: 2019/10/26 12:28:35 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** returns 0 if quad pl1-pl2 intersects with a wall
*/

int		walls_collision(t_doom *doom, t_xy pl1, t_xy pl2)
{
	t_sectors	*sect;
	t_xy		*v;
	int			n;
	t_xy		pos1;
	t_xy		pos2;
	t_xy		hole;
	t_xy		move_pos;
	float		height;

	sect = &doom->sectors[doom->player.sector];
	v = sect->vert;
	n = 0;
	height = doom->player.sit ? DuckHeight : EyeHeight;
	while (n < sect->npoints)
	{
		pos1 = v2_addf(v[n], doom->wall_col_size);
		pos2 = v2_addf(v[n + 1], -doom->wall_col_size);
		if (IntersectBox(pl1.x, pl1.y, pl2.x, pl2.y, pos1.x, pos1.y, pos2.x, pos2.y))
		{
			hole.x = sect->neighbors[n] < 0 ? 9e9 : max(sect->floor, doom->sectors[sect->neighbors[n]].floor);
			hole.y = sect->neighbors[n] < 0 ? -9e9 : min(sect->ceil, doom->sectors[sect->neighbors[n]].ceil);
			if (hole.y < doom->player.where.z + HeadMargin ||
				hole.x > doom->player.where.z - EyeHeight + KneeHeight)
				return (0);
		}
		n++;
	}
	return (1);
}

/*
** returns 0 if quad pl1-pl2 intersected with obj collider
*/

int		obj_collision(t_doom *doom, t_xy player)
{
	int		n;
	t_obj	obj;

	n = 0;
	while (n < doom->num.objs)
	{
		obj = doom->objs[n];
		if (obj.col_passable || !obj.enabled)
		{
			n++;
			continue ;
		}
		if (collision_circle(player, doom->player.col_size, obj.p, obj.col_size))
			return (0);
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
	doom->player.psin = sinf(doom->player.angle);
	doom->player.pcos = cosf(doom->player.angle);
	return (1);
}

/*
** returns 1 if found interactable obj in closest proximity
*/

int		find_obj_interaction(t_doom *doom)
{
	int		n;
	t_obj	*obj;
	t_xy	p;
	t_xy	d;

	p = (t_xy){doom->player.where.x, doom->player.where.y};
	d = (t_xy){doom->player.pcos * 4, doom->player.psin * 4};
	n = 0;
	while (n < doom->num.objs)
	{
		obj = &doom->objs[n];
		if (!obj->enabled || obj->on_interaction == NULL)
		{
			n++;
			continue ;
		}
		if (collision_box(p, v2_add(p, d), v2_addf(obj->p, -obj->col_size), v2_addf(obj->p, obj->col_size)))
		{
			obj->on_interaction(doom, obj);
			printf("Player interacted with obj %d\n", obj->id);
			return (1);
		}
		n++;
	}
	return (0);
}

int		rgb_mix(int rgb1, int rgb2, float percent)
{
	float percent2;

	percent = clamp(percent, 0, 1);
	percent2 = 1 - percent;
	rgb1 = ((int)(((rgb1 >> 16) & 0xff) * percent +
				((rgb2 >> 16) & 0xff) * percent2) << 16) |
			((int)(((rgb1 >> 8) & 0xff) * percent +
				((rgb2 >> 8) & 0xff) * percent2) << 8) |
			((int)((rgb1 & 0xff) * percent +
				(rgb2 & 0xff) * percent2));
	return (rgb1);
}

int		player_blood_update(t_doom *doom)
{
	int		i;
	int		size;
	float	intensity;

	intensity = doom->player.blood;
	if (intensity <= 0)
		return (0);
	size = WIDTH * HEIGHT;
	i = 0;
	while (i < size)
	{
		doom->sdl->pix[i] = rgb_mix(0xff0000, doom->sdl->pix[i], intensity);
		i++;
	}
	doom->player.blood -= doom->fps.time_frame;
	doom->player.blood = clamp(doom->player.blood, 0.0f, 1.0f);
	return (1);
}

int		player_take_damage(t_doom *doom, int damage)
{
	if (doom->player.hp < 0)
		return (0);
	doom->player.blood = 0.4f;
	doom->player.hp -= damage;
	if (!doom->player.dead)
		play_sound(doom, SOUND_DAMAGE);
	if (doom->player.hp <= 0)
	{
		if (!doom->player.dead)
			play_sound(doom, SOUND_SCREAM);
		doom->player.blood = 1.0f;
		doom->player.dead = 1;
		doom->player.where.z = doom->sectors[doom->player.sector].floor + 2;
		printf("You are dead!\n");
	}
	return (1);
}
