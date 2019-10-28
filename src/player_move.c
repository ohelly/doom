/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:24:41 by njacobso          #+#    #+#             */
/*   Updated: 2019/10/28 19:40:14 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		sqr(int x)
{
	return (x * x);
}

/*
**	l1, l2 - точки отрезка, к которому ищем расстояние
**	p - точка, от которой ищем расстояние
**	hit - проекция точки на отрезок
**	Возвращает расстояние между отрезком и точкой
*/

float	line_distance(t_xy l1, t_xy l2, t_xy p)
{
	float	dist;
	float	t;
	t_xy	proj;

	dist = (sqr(l1.x - l2.x) + sqr(l1.y - l2.y));
	if (dist == 0)
		return (distance(l1, p));
	t = ((p.x - l1.x) * (l2.x - l1.x) +
	(p.y - l1.y) * (l2.y - l1.y)) / dist;
	t = clamp(t, 0, 1);
	proj.x = l1.x + t * (l2.x - l1.x);
	proj.y = l1.y + t * (l2.y - l1.y);
	dist = distance(p, proj);
	return (dist);
}

/*
**	Возвращает 1, если стена i ближе чем player.col_size
*/

int		intersect_walls(t_doom *doom, t_xy pl, int i)
{
	t_xy		pos1;
	t_xy		pos2;
	t_sectors	*sect;

	sect = &doom->sectors[doom->player.sector];
	pos1 = sect->vert[i];
	pos2 = sect->vert[i + 1];
	if (line_distance(pos1, pos2, pl) < doom->player.col_size)
		return (1);
	return (0);
}

/*
** returns 0 if circle pl + pl->col_size intersects with a wall
*/

int		walls_collision(t_doom *doom, t_xy pl)
{
	t_sectors	*sect;
	t_xy		*v;
	int			n;
	t_xy		hole;
	t_xy		move_pos;
	float		height;

	sect = &doom->sectors[doom->player.sector];
	v = sect->vert;
	n = 0;
	height = doom->player.sit ? DuckHeight : EyeHeight;
	while (n < sect->npoints)
	{
		if (intersect_walls(doom, pl, n) == 1)
		{
			hole.x = sect->neighbors[n] < 0 ? 9e9 :
			max(sect->floor, doom->sectors[sect->neighbors[n]].floor);
			hole.y = sect->neighbors[n] < 0 ? -9e9 :
			min(sect->ceil, doom->sectors[sect->neighbors[n]].ceil);
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
		if (collision_circle(player, doom->player.col_size,
		obj.p, obj.col_size))
			return (0);
		n++;
	}
	return (1);
}

int		player_move(t_doom *doom, t_xy delta)
{
	t_xy		player;
	t_xy		move_pos;
	t_xy		pl;

	player = (t_xy){doom->player.where.x, doom->player.where.y};
	move_pos = v2_add(player, (t_xy){delta.x, 0});
	pl = move_pos;
	delta.x *= walls_collision(doom, pl);
	move_pos = v2_add(player, (t_xy){0, delta.y});
	pl = move_pos;
	delta.y *= walls_collision(doom, pl);
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
		if (collision_box(p, v2_add(p, d), v2_addf(obj->p, -obj->col_size),
		v2_addf(obj->p, obj->col_size)))
		{
			obj->on_interaction(doom, obj);
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
	}
	return (1);
}
