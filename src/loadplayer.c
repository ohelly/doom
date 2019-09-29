/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadplayer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 14:22:21 by dtoy              #+#    #+#             */
/*   Updated: 2019/09/28 15:56:28 by dtoy             ###   ########.fr       */
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
	printf("Angle - %f\n", player->angle);
	player->anglesin = sinf(player->angle);
	player->anglecos = cosf(player->angle);
	
	printf("anglesin - %f\n", player->anglesin);
	printf("anglecos - %f\n", player->anglecos);
	printf("x - %f\n", player->where.x);
	printf("y - %f\n", player->where.y);

	return (0);
}
