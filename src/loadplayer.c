/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadplayer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 14:22:21 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/29 04:46:08 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	default_player_params(t_player *player)
{
	int		n;

	n = 0;
	while (n < 4)
	{
		if (n == player->weapon)
			player->allweapons[n] = 1;
		else
			player->allweapons[n] = 0;
		n++;
	}
	player->allweapons[0] = 1;
	player->psin = sinf(player->angle);
	player->pcos = cosf(player->angle);
	player->fall = 0;
	player->ground = !player->fall;
	player->move = 0;
	player->sit = 0;
	player->stand = 1;
	player->yaw = 0;
	player->velocity.x = 0;
	player->velocity.y = 0;
	player->velocity.z = 0;
	player->col_size = 1.0f;
}

int		loadplayer(t_player *player, char *str)
{
	float	tmp;

	str = todigit(str, &tmp);
	player->where.y = tmp / 4.f;
	str = todigit(str, &tmp);
	player->where.x = tmp / 4.f;
	str = todigit(str, &player->angle);
	str = todigit(str, &tmp);
	player->sector = (int)tmp;
	player->start = player->sector;
	str = todigit(str, &tmp);
	player->hp = (int)tmp;
	str = todigit(str, &tmp);
	player->weapon = (int)tmp;
	str = todigit(str, &tmp);
	player->end = (int)tmp;
	default_player_params(player);
	return (0);
}
