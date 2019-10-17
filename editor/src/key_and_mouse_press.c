/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_and_mouse_press.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 22:12:24 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/15 14:35:56 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void	key_press_three(t_doom *doom)
{
	if (doom->sdl->ev.key.keysym.sym == SDLK_LEFT)
		doom->move_vector = (t_v2){ -1, doom->move_vector.y };
	else if (doom->sdl->ev.key.keysym.sym == SDLK_RIGHT)
		doom->move_vector = (t_v2){ 1, doom->move_vector.y };
	else
		doom->move_vector = (t_v2){ 0, doom->move_vector.y };
	if (doom->sdl->ev.key.keysym.sym == SDLK_UP)
		doom->move_vector = (t_v2){ doom->move_vector.x, -1 };
	else if (doom->sdl->ev.key.keysym.sym == SDLK_DOWN)
		doom->move_vector = (t_v2){ doom->move_vector.x, 1 };
	else
		doom->move_vector = (t_v2){ doom->move_vector.x, 0 };
	if (doom->sdl->ev.key.keysym.sym == '\033')
		exit(0);
	if (doom->sdl->ev.key.keysym.sym == 's')
		get_closest_sector(doom);
}

void	key_press_two(t_doom *doom)
{
	if (doom->sdl->ev.key.keysym.sym == '1')
	{
		doom->app = 0;
		doom->walls->selected_wall = -1;
		doom->sects->selected_sector = -1;
		doom->obj->select_obj = -1;
		doom->aspr->select_spr = -1;
	}
	if (doom->sdl->ev.key.keysym.sym == '2')
	{
		doom->app = 2;
		doom->walls->selected_wall = -1;
		doom->sects->selected_sector = 0;
		doom->obj->select_obj = -1;
		doom->aspr->select_spr = -1;
	}
	if (doom->sdl->ev.key.keysym.sym == '3')
	{
		doom->app = 3;
		doom->walls->selected_wall = -1;
		doom->sects->selected_sector = -1;
		doom->obj->select_obj = 0;
		doom->aspr->select_spr = -1;
	}
	key_press_three(doom);
}

void	key_press_one(t_doom *doom)
{
	if (doom->app < 2)
	{
		if (doom->sdl->ev.key.keysym.sym == ' ')
			build_sector(doom);
		if (doom->sdl->ev.key.keysym.sym == 'e')
			save(doom);
		if (doom->sdl->ev.key.keysym.sym == 'w')
			find_portal(doom);
		if (doom->sdl->ev.key.keysym.sym == '\r')
			if (doom->walls->selected_wall != -1)
				build_portal(doom, doom->walls->selected_wall,
				doom->walls->adjacent_wall);
		if (doom->sdl->ev.key.keysym.sym == 'v')
			split_wall(doom);
		if (doom->sdl->ev.key.keysym.sym == 'l')
			split_sectors(doom);
		if (doom->sdl->ev.key.keysym.sym == 'c')
			remove_built_sector(doom);
		if (doom->sdl->ev.key.keysym.sym == 'p')
			set_sprite_on_wall(doom);
		if (doom->sdl->ev.key.keysym.sym == 'o')
			set_object(doom);
	}
	key_press_two(doom);
}

void	key_and_mouse_press(t_doom *doom)
{
	while (SDL_PollEvent(&doom->sdl->ev))
	{
		if (doom->sdl->ev.type == SDL_KEYDOWN)
			key_press_one(doom);
		if (doom->app == 2 || doom->app == 3)
			if (doom->sdl->ev.type == SDL_MOUSEBUTTONDOWN)
				mouse_press(doom, doom->sdl, doom->app);
		if (doom->sdl->ev.type == SDL_MOUSEMOTION)
		{
			*doom->mouse = (t_mouse){ doom->sdl->ev.motion.x,
			doom->sdl->ev.motion.y, 0, 0 };
			doom->move_vector = (t_v2){0, 0};
		}
		output(doom);
	}
}
