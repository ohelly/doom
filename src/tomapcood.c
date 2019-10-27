/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tomapcood.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:21:01 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/27 20:47:41 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	to_absolute_ones(float *X, float *Z, t_player player) \
{
	float rtx = (*Z) * player.pcos + (*X) * player.psin; \
    float rtz = (*Z) * player.psin - (*X) * player.pcos; \
    *X = rtx + player.where.x; *Z = rtz + player.where.y; \
}

void	to_map_coordinates(float mapY, int screenX, int screenY, float *X, float *Z, t_player player)
{
    *Z = (mapY) * HEIGHT * VFOV / ((HEIGHT / 2 - (screenY)) - player.yaw * HEIGHT * VFOV); \
    *X = (*Z) * (WIDTH / 2 - (screenX)) / (WIDTH * HFOV); \
    to_absolute_ones(X, Z, player);
}
