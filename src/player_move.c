/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:24:41 by njacobso          #+#    #+#             */
/*   Updated: 2019/10/29 00:49:46 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
