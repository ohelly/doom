/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadgame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 18:13:26 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/30 21:11:53 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		init_sdl(t_sdl *sdl)
{
	SDL_Surface	*surface;

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	sdl->win = SDL_CreateWindow("Doom", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	surface = SDL_GetWindowSurface(sdl->win);
	sdl->pix = (int*)surface->pixels;
	return (0);
}

void	fps(t_fps *fps)
{
	fps->times[1] = fps->times[0];
	fps->times[0] = SDL_GetTicks();
	fps->time_frame = (fps->times[0] - fps->times[1]) / 1000;
	fps->fps_count++;
	fps->fps_total += fps->time_frame;
}

int		calc_mouse(t_doom *doom, float yaw)
{
	int	x;
	int	y;

	if (doom->menu.s)
		menu_mouse(doom, 0);
	else
	{
		SDL_GetRelativeMouseState(&x, &y);
		/*if (doom->menu.r)
		{
			doom->menu.r = 0;
			x = 0;
			y = 0;
		}*/
		if (doom->player.dead)
			return (0);
		doom->player.yaw = CLAMP(yaw + y * 0.01f, -5, 5);
		doom->player.angle += x * 0.003f;
		doom->player.psin = sinf(doom->player.angle);
		doom->player.pcos = cosf(doom->player.angle);
	}
	return (0);
}

int		load_game(t_doom *doom)
{
	SDL_Event	ev;

	init_sdl(doom->sdl);
	load_fonts(doom);
	load_menu(doom);
	calc_mouse(doom, doom->player.yaw);
	doom->menu.s = 1;
	while (1)
	{
		SDL_SetRelativeMouseMode(!doom->menu.s);
		fps(&doom->fps);
		animation(doom, doom->fps);
		doors(doom, doom->player, doom->fps);
		draw_screen(doom);
		objects_update(doom);
		enemies_update(doom);
		player_blood_update(doom);
		calc_jump(&doom->player, doom->sectors, doom->fps);
		if (doom->player.move == 1)
			calc_is_wall(doom, &doom->player);
		while (SDL_PollEvent(&ev))
			hooks(doom, ev);
		calc_mouse(doom, doom->player.yaw);
		calc_move(doom, &doom->player);
		SDL_UpdateWindowSurface(doom->sdl->win);
		if (doom->a)
			doom->a = 0;
	}
	return (0);
}
