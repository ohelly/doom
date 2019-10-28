/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 19:48:11 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/29 01:42:16 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	weapon_sounds(t_doom *doom, int weapon)
{
	if (weapon == WEAPON_FOOT)
		play_sound(doom, SOUND_FOOT);
	if (weapon == WEAPON_PISTOL)
		play_sound(doom, SOUND_PISTOL);
	if (weapon == WEAPON_SHOTGUN)
		play_sound(doom, SOUND_SHOTGUN);
	if (weapon == WEAPON_RIPPER)
		play_sound(doom, SOUND_RIPPER);
}

int		shoot(t_doom *doom)
{
	int		i;

	weapon_sounds(doom, doom->player.weapon);
	i = -1;
	while (++i < 32)
	{
		if (doom->obj_ind[i] == 1)
		{
			if (find_on_hit_obj(doom) >= 3)
				break ;
		}
	}
	if (doom->player.weapon)
		shoot_wall(doom, doom->player, doom->sectors, doom->pics);
	find_pic_interaction(doom, doom->player, doom->pics);
	return (0);
}

void	left_mouse_keydown(t_doom *doom, SDL_Event ev,
t_weapon *weapon, t_player *player)
{
	if (ev.button.button == SDL_BUTTON_LEFT &&
	!player->reload && weapon->ammo && !weapon->states_frame)
	{
		doom->lkey = 1;
		if (player->weapon)
			weapon->ammo--;
		if (weapon->anim_frame == 0)
			weapon->states_frame = 1;
		if (player->weapon == WEAPON_PISTOL)
		{
			player->shoots++;
			if (player->shoots == 10)
			{
				player->shoots = 0;
				player->reload = 1;
			}
		}
		shoot(doom);
	}
}
