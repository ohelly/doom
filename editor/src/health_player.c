/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 02:35:27 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/29 02:40:54 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void		health_player(int x, int y, t_player *player)
{
	if (x >= 950 && x <= 1000 && y >= 410 && y <= 460)
	{
		if (player->hp > 1)
			player->hp--;
	}
	else
	{
		if (player->hp < 100)
			player->hp++;
	}
}
