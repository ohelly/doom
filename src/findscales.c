/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findscales.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:18:48 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/28 17:19:54 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			find_scales(t_doom *doom, t_cood *cood, t_player player)
{
	cood->scale1.x = (HFOV * WIDTH) / cood->t1.z;
	cood->scale1.y = (VFOV * HEIGHT) / cood->t1.z;
	cood->scale2.x = (HFOV * WIDTH) / cood->t2.z;
	cood->scale2.y = (VFOV * HEIGHT) / cood->t2.z;
	cood->w1x = WIDTH / 2 - (int)(cood->t1.x * cood->scale1.x);
	cood->w2x = WIDTH / 2 - (int)(cood->t2.x * cood->scale2.x);
	if (cood->w1x == cood->w2x)
		return (0);
	return (1);
}

int			find_nyceil_nyfloor(t_doom *doom, t_sectors *s,
t_cood *cood, t_player player)
{
	cood->nyceil = doom->sectors[cood->neighbor].ceil - player.where.z;
	cood->nyfloor = doom->sectors[cood->neighbor].floor - player.where.z;
	cood->n1y.a = HEIGHT / 2 - (int)
	(yaw(cood->nyceil, cood->t1.z, player) * cood->scale1.y);
	cood->n1y.b = HEIGHT / 2 - (int)
	(yaw(cood->nyfloor, cood->t1.z, player) * cood->scale1.y);
	cood->n2y.a = HEIGHT / 2 - (int)
	(yaw(cood->nyceil, cood->t2.z, player) * cood->scale2.y);
	cood->n2y.b = HEIGHT / 2 - (int)
	(yaw(cood->nyfloor, cood->t2.z, player) * cood->scale2.y);
	return (0);
}

int			find_yceil_yfloor(t_doom *doom, t_sectors *s,
t_cood *cood, t_player player)
{
	cood->yceil = s->ceil - player.where.z;
	cood->yfloor = s->floor - player.where.z;
	cood->neighbor = s->neighbors[cood->n];
	if (cood->neighbor >= 0)
		find_nyceil_nyfloor(doom, s, cood, player);
	cood->w1y.a = HEIGHT / 2 - (int)
	(yaw(cood->yceil, cood->t1.z, player) * cood->scale1.y);
	cood->w1y.b = HEIGHT / 2 - (int)
	(yaw(cood->yfloor, cood->t1.z, player) * cood->scale1.y);
	cood->w2y.a = HEIGHT / 2 - (int)
	(yaw(cood->yceil, cood->t2.z, player) * cood->scale2.y);
	cood->w2y.b = HEIGHT / 2 - (int)
	(yaw(cood->yfloor, cood->t2.z, player) * cood->scale2.y);
	return (0);
}
