/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tomapcood.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:21:01 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/29 06:06:00 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"


void	to_absolute_ones(t_xyz *map, t_player player)
{
	float rtx;
	float rtz;

	rtx = (map->z) * player.pcos + (map->x) * player.psin;
	rtz = (map->z) * player.psin - (map->x) * player.pcos;
	map->x = rtx + player.where.x;
	map->z = rtz + player.where.y;
}

void	to_map_coordinates(t_cf *p, t_xyz *map, t_player player)
{
	map->z = (p->hei) * HEIGHT * VFOV /
	((HEIGHT / 2 - (p->y)) - player.yaw * HEIGHT * VFOV);
	map->x = (map->z) * (WIDTH / 2 - (p->x)) / (WIDTH * HFOV);
	to_absolute_ones(map, player);
}
