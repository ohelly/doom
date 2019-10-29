/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadgame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 18:13:26 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/29 15:08:12 by dtoy             ###   ########.fr       */
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
	SDL_SetRelativeMouseMode(1);
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

int		calc_mouse(t_player *player, float yaw)
{
	int		x;
	int		y;

	if (player->dead)
		return (0);
	SDL_GetRelativeMouseState(&x, &y);
	player->yaw = CLAMP(yaw + y * 0.01f, -5, 5);
	player->angle += x * 0.003f;
	player->psin = sinf(player->angle);
	player->pcos = cosf(player->angle);
	return (0);
}

int		load_game(t_doom *doom)
{
	SDL_Event	ev;

	init_sdl(doom->sdl);
	loadfonts(doom->hud);
	while (1)
	{
		fps(&doom->fps);
		animation(doom, doom->fps);
		doors(doom, doom->player, doom->fps);
		draw_screen(doom);
		objects_update(doom);
		enemies_update(doom);
		player_blood_update(doom);
		calc_jump(&doom->player, doom->sectors, doom->fps);
		if (doom->player.move == 1)
			calc_is_wall(doom, &doom->player);;
		while (SDL_PollEvent(&ev))
			hooks(doom, ev);;
		calc_mouse(&doom->player, doom->player.yaw);;
		calc_move(doom, &doom->player);;
		SDL_UpdateWindowSurface(doom->sdl->win);
		if (doom->a)
			doom->a = 0;
	}
	return (0);
}
