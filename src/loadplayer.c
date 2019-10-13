/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadplayer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 14:22:21 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/11 15:35:20 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		loadplayer(t_player *player, char *str)
{
	float	tmp;

	str = todigit(str, &player->where.y);
	str = todigit(str, &player->where.x);
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
	printf("Angle - %f\n", player->angle);
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
	printf("anglesin - %f\n", player->psin);
	printf("anglecos - %f\n", player->pcos);
	printf("x - %f\n", player->where.x);
	printf("y - %f\n", player->where.y);

	return (0);
}
