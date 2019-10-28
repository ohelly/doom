/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 19:49:21 by glormell          #+#    #+#             */
/*   Updated: 2019/10/28 19:50:38 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
**	N NE E SE S SW W WN
*/

int		rotate_enemy(t_doom *doom, t_enemy *enemy)
{
	float	player_deg;
	float	enemy_deg;
	float	angle;
	int		state;

	player_deg = v2_to_rot(v2_subtract((t_xy){doom->player.where.x,
					doom->player.where.y}, enemy->obj->p));
	player_deg = rad_to_deg(player_deg);
	enemy_deg = enemy->rot;
	enemy_deg = rad_to_deg(enemy_deg);
	angle = enemy_deg - player_deg + 22.5f;
	if (angle < 0)
		angle += 360;
	state = (int)(angle / 45);
	return (state);
}

void	enemies_update(t_doom *doom)
{
	int		i;
	t_enemy *enemy;

	i = 0;
	while (i < doom->num.enemies)
	{
		enemy = &doom->enemies[i];
		if (enemy->obj->enabled && enemy->health > 0)
			enemy->on_framestart(doom, enemy);
		i++;
	}
}
