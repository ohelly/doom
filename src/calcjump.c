/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_jump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 19:22:11 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/27 19:22:31 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	player_on_ground(t_player *player, t_sectors *s, float height)
{
	player->where.z = s->floor + height;
	player->velocity.z = 0;
	player->fall = 0;
	player->ground = 1;
}

int		calc_jump(t_doom *doom, t_player *player, t_sectors *sectors, t_fps fps)
{
	float	nextz;
	float	height;

	height = player->sit ? DuckHeight : EyeHeight;
	player->ground = !player->fall;
	if (player->fall)
	{
		player->velocity.z -= fps.time_frame * 5.f;
		nextz = player->where.z + player->velocity.z;
		if (player->velocity.z < 0 &&
		nextz < sectors[player->sector].floor + height)
			player_on_ground(player, &sectors[player->sector], height);
		else if (player->velocity.z > 0 && nextz > sectors[player->sector].ceil)
		{
			player->velocity.z = 0;
			player->fall = 1;
		}
		if (player->fall)
		{
			player->where.z += player->velocity.z;
			player->move = 1;
		}
	}
	return (0);
}
