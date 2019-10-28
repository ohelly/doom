/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:59:36 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/27 20:59:44 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		wpn_state_change(t_weapon *wpn, int state)
{
	if (state >= wpn->states_count ||
		state < 0 || state == wpn->states_frame)
		return ;
	wpn->states_frame = state;
	wpn->anim_frame = 0;
}

void		wpn_anim_next(t_doom *doom, t_player *player,
t_weapon *wpn, t_fps fps)
{
	static float t = 0;

	if (player->reload && t == 0 && !wpn->anim_frame)
		play_sound(doom, SOUND_RELOAD);
	t += fps.time_frame;
	if (t >= wpn->delay)
	{
		wpn->anim_frame++;
		if (wpn->anim_frame >= wpn->anim_count[wpn->states_frame] ||
			wpn->images[wpn->states_frame][wpn->anim_frame] == -1)
		{
			if (wpn->states_frame == 2)
				player->reload = 0;
			if (wpn->type != WEAPON_RIPPER)
				wpn_state_change(wpn, 0);
			wpn->anim_frame = 0;
		}
		t = 0;
	}
}

t_img		wpn_get_image(t_doom *doom, t_weapon *wpn)
{
	return (doom->img[wpn->images[wpn->states_frame][wpn->anim_frame]]);
}
