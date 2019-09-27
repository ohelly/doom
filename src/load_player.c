/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:56:58 by dtoy              #+#    #+#             */
/*   Updated: 2019/09/19 15:18:17 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		loadplayer(t_player *player, char *str)
{
	size_t		j;
	int		t;

	t = 0;
	j = 0;
	printf("\n");
	while (j < ft_strlen(str))
	{
		if (ft_isdigit(str[j]) && t == 0)
		{
			player->where.y = atoi(&str[j]);
			printf("Py - %f\n", player->where.y);
			t = 1;
			while (ft_isdigit(str[j]) || str[j] == '.')
				j++;
		}
		else if (ft_isdigit(str[j]) && t == 1)
		{
			player->where.x = atoi(&str[j]);
			printf("Px - %f\n", player->where.x);
			t = 2;
			while (ft_isdigit(str[j]) || str[j] == '.')
				j++;
		}
		else if (ft_isdigit(str[j]) && t == 2)
		{
			player->angle = atoi(&str[j]);
			printf("Angle - %f\n", player->angle);
			t = 3;
			while (ft_isdigit(str[j]) || str[j] == '.')
				j++;
		}
		else if (ft_isdigit(str[j]) && t == 3)
		{
			player->sector = atoi(&str[j]);
			printf("Sector - %d\n", player->sector);
			t = 4;
			while (ft_isdigit(str[j]) || str[j] == '.')
				j++;
		}
		else
			j++;
	}
	player->velocity.x = 0;
	player->velocity.y = 0;
	player->velocity.z = 0;
	return (0);
}
