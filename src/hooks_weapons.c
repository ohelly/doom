/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_weapons.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 19:50:38 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/28 19:51:05 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	change_weapon(t_player *player, t_weapon *weapon, int n)
{
	player->weapon = n;
	weapon[player->weapon].anim_frame = 0;
	weapon[player->weapon].states_frame = 0;
}

void	change_all_weapons(t_weapon *weapon, SDL_Event ev,
t_player *player, int *allweapons)
{
	if (ev.key.keysym.sym == '1' && allweapons[WEAPON_FOOT])
		change_weapon(player, weapon, WEAPON_FOOT);
	if (ev.key.keysym.sym == '2' && allweapons[WEAPON_PISTOL])
		change_weapon(player, weapon, WEAPON_PISTOL);
	if (ev.key.keysym.sym == '3' && allweapons[WEAPON_SHOTGUN])
		change_weapon(player, weapon, WEAPON_SHOTGUN);
	if (ev.key.keysym.sym == '4' && allweapons[WEAPON_RIPPER])
		change_weapon(player, weapon, WEAPON_RIPPER);
}

void	reload_pistol(SDL_Event ev, t_doom *doom,
t_weapon weapon, t_player *player)
{
	if (ev.key.keysym.sym == 'r' && player->weapon ==
	WEAPON_PISTOL && weapon.ammo > 10 && player->shoots)
	{
		play_sound(doom, SOUND_RELOAD);
		player->reload = 1;
		player->shoots = 0;
	}
}
