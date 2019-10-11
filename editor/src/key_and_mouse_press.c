/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_and_mouse_press.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 22:12:24 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/11 17:22:43 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void	key_and_mouse_press(t_doom *doom)
{
	while (SDL_PollEvent(&doom->sdl->ev))
	{
		if (doom->sdl->ev.type == SDL_KEYDOWN)
		{
			if (doom->sdl->ev.key.keysym.sym == '\033')
				exit(0);
			if (doom->app < 2)
			{
				if (doom->sdl->ev.key.keysym.sym == ' ')
					build_sector(doom);
				if (doom->sdl->ev.key.keysym.sym == 'e')
					save(doom);
				if (doom->sdl->ev.key.keysym.sym == 'w')
					find_portal(doom);
				if (doom->sdl->ev.key.keysym.sym == 's')
					get_closest_sector(doom);
				if (doom->sdl->ev.key.keysym.sym == '\r')
					if (doom->walls->selected_wall != -1)
						build_portal(doom);
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
			if (doom->app == 2)
				if (doom->sdl->ev.key.keysym.sym == 's')
					get_closest_sector(doom);
			if (doom->sdl->ev.key.keysym.sym == '1')
			{
				doom->app = 0;
				doom->walls->selected_wall = -1;
				doom->sects->selected_sector = -1;
			}
			if (doom->sdl->ev.key.keysym.sym == '2')
			{
				doom->app = 2;
				doom->walls->selected_wall = -1;
				doom->sects->selected_sector = 0;
			}
			if (doom->sdl->ev.key.keysym.sym == '3')
			{
				doom->app = 3;
				doom->walls->selected_wall = -1;
				doom->sects->selected_sector = -1;
			}
			if (doom->sdl->ev.key.keysym.sym == SDLK_LEFT)
				doom->move_vector = (t_v2){-1, doom->move_vector.y};
			else if (doom->sdl->ev.key.keysym.sym == SDLK_RIGHT)
				doom->move_vector = (t_v2){1, doom->move_vector.y};
			else
				doom->move_vector = (t_v2){0, doom->move_vector.y};
			if (doom->sdl->ev.key.keysym.sym == SDLK_UP)
				doom->move_vector = (t_v2){doom->move_vector.x, -1};
			else if (doom->sdl->ev.key.keysym.sym == SDLK_DOWN)
				doom->move_vector = (t_v2){doom->move_vector.x, 1};
			else
				doom->move_vector = (t_v2){doom->move_vector.x, 0};
			
		}
		if (doom->app == 2)
		{
			if (doom->sdl->ev.type == SDL_MOUSEBUTTONDOWN)
			{
				if (doom->sdl->ev.button.button == SDL_BUTTON_LEFT)
					mouse_press_left(doom, doom->sdl->ev.button.x, doom->sdl->ev.button.y);
				if (doom->sdl->ev.button.button == SDL_BUTTON_RIGHT)
					mouse_press_right(doom, doom->sdl->ev.button.x, doom->sdl->ev.button.y);
			}
		}
		if (doom->sdl->ev.type == SDL_MOUSEMOTION)
		{
			*doom->mouse = (t_mouse){ doom->sdl->ev.motion.x, doom->sdl->ev.motion.y, 0 , 0 };
			doom->move_vector = (t_v2){0, 0};
		}
		printf("floor = %d  ceil = %d\n", doom->sects->sectors[doom->sects->selected_sector].floor, doom->sects->sectors[doom->sects->selected_sector].ceiling);
		output(doom);
	}
}