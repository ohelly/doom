/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcmove.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 19:23:25 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/27 19:23:44 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	change_move_vec(float *move_vec, t_player *player, float speed, char c)
{
	if (c == '+')
	{
		move_vec[0] += player->pcos * speed;
		move_vec[1] += player->psin * speed;
	}
	else
	{
		move_vec[0] -= player->pcos * speed;
		move_vec[1] -= player->psin * speed;
	}
}

int		direction(t_doom *doom, t_player *player, float *move_vec, t_fps fps)
{
	float	speed;

	speed = player->sprint ? 0.7f : 0.4f;
	if (doom->wsad[0])
		change_move_vec(move_vec, player, speed, '+');
	if (doom->wsad[1])
		change_move_vec(move_vec, player, speed, '-');
	if (doom->wsad[2])
	{
		move_vec[0] += player->psin * speed;
		move_vec[1] -= player->pcos * speed;
	}
	if (doom->wsad[3])
	{
		move_vec[0] -= player->psin * speed;
		move_vec[1] += player->pcos * speed;
	}
	move_vec[0] *= fps.time_frame * 60.f;
	move_vec[1] *= fps.time_frame * 60.f;
	return (0);
}

int		calc_move(t_doom *doom, t_player *player)
{
	float	move_vec[2];
	float	acceleration;

	move_vec[0] = 0.f;
	move_vec[1] = 0.f;
	if (player->dead)
		return (0);
	direction(doom, player, move_vec, doom->fps);
	doom->push = doom->wsad[0] || doom->wsad[1]
	|| doom->wsad[2] || doom->wsad[3];
	acceleration = doom->push ? 0.6 : 0.4;
	player->velocity.x = player->velocity.x * (1 - acceleration)
	+ move_vec[0] * acceleration;
	player->velocity.y = player->velocity.y * (1 - acceleration)
	+ move_vec[1] * acceleration;
	if (doom->push == 1)
		player->move = 1;
	return (0);
}
