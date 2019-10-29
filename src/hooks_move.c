/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 19:51:18 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/29 01:56:34 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	jump_sprint_crouch(t_doom *doom, SDL_Event ev,
t_player *player, t_sectors *s)
{
	if (ev.key.keysym.sym == SDLK_SPACE)
	{
		if (player->ground)
		{
			play_sound(doom, SOUND_JUMP);
			player->velocity.z = 2.f;
			player->fall = 1;
		}
	}
	if (ev.key.keysym.sym == SDLK_LCTRL)
	{
		player->sit = 1;
		player->where.z = s[player->sector].floor + DUCKHEIGHT;
	}
	if (ev.key.keysym.sym == SDLK_LSHIFT)
		player->sprint = 1;
}
