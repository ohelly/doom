/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 18:28:42 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/28 19:54:55 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	player_move_keydown(SDL_Event ev, int *wsad)
{
	if (ev.key.keysym.sym == 'w')
		wsad[0] = 1;
	if (ev.key.keysym.sym == 's')
		wsad[1] = 1;
	if (ev.key.keysym.sym == 'a')
		wsad[2] = 1;
	if (ev.key.keysym.sym == 'd')
		wsad[3] = 1;
}

int		keydown(t_doom *doom, SDL_Event ev)
{
	close_program(ev, doom);
	if (doom->player.dead)
		return (0);
	change_all_weapons(doom->weapon, ev,
	&doom->player, doom->player.allweapons);
	reload_pistol(ev, doom, doom->weapon[WEAPON_PISTOL], &doom->player);
	player_move_keydown(ev, doom->wsad);
	if (ev.key.keysym.sym == 'e')
		if (find_door(doom, doom->player) ||
		find_pic_interaction(doom, doom->player, doom->pics)
		|| find_obj_interaction(doom))
			play_sound(doom, SOUND_INTERACT);
	jump_sprint_crouch(doom, ev, &doom->player, doom->sectors);
	if (ev.key.keysym.sym == 'p')
	{
		profile_output(doom);
	}
	return (0);
}

void	player_move_keyup(SDL_Event ev, int *wsad)
{
	if (ev.key.keysym.sym == 'w')
		wsad[0] = 0;
	if (ev.key.keysym.sym == 's')
		wsad[1] = 0;
	if (ev.key.keysym.sym == 'a')
		wsad[2] = 0;
	if (ev.key.keysym.sym == 'd')
		wsad[3] = 0;
}

int		keyup(t_doom *doom, SDL_Event ev)
{
	if (doom->player.dead)
		return (0);
	player_move_keyup(ev, doom->wsad);
	if (ev.button.button == SDL_BUTTON_LEFT)
		doom->lkey = 0;
	if (ev.button.button == SDL_BUTTON_RIGHT)
		doom->rkey = 0;
	if (ev.key.keysym.sym == SDLK_LCTRL)
	{
		doom->player.sit = 0;
		doom->player.where.z =
		doom->sectors[doom->player.sector].floor + EyeHeight;
	}
	if (ev.key.keysym.sym == SDLK_LSHIFT)
		doom->player.sprint = 0;
	return (0);
}

int		hooks(t_doom *doom, SDL_Event ev)
{
	if (ev.type == SDL_MOUSEBUTTONDOWN)
	{
		left_mouse_keydown(doom, ev,
		&doom->weapon[doom->player.weapon], &doom->player);
		if (ev.button.button == SDL_BUTTON_RIGHT)
			doom->rkey = 1;
	}
	if (ev.type == SDL_MOUSEBUTTONUP)
	{
		if (ev.button.button == SDL_BUTTON_LEFT)
			doom->lkey = 0;
		if (ev.button.button == SDL_BUTTON_RIGHT)
			doom->rkey = 0;
	}
	if (ev.type == SDL_KEYDOWN)
		keydown(doom, ev);
	if (ev.type == SDL_KEYUP)
		keyup(doom, ev);
	return (0);
}
