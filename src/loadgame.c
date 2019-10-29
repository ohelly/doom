/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadgame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 18:13:26 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/29 18:21:25 by dtoy             ###   ########.fr       */
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
		//printf("1\n");
		fps(&doom->fps);
		//printf("2\n");
		animation(doom, doom->fps);
		//printf("3\n");
		doors(doom, doom->player, doom->fps);
		//printf("4\n");
		draw_screen(doom);
		//printf("5\n");
		objects_update(doom);
		//printf("6\n");
		enemies_update(doom);
		//printf("7\n");
		player_blood_update(doom);
		//printf("8\n");
		calc_jump(&doom->player, doom->sectors, doom->fps);
		//printf("9\n");
		if (doom->player.move == 1)
			calc_is_wall(doom, &doom->player);;
		//	printf("10\n");
		while (SDL_PollEvent(&ev))
			hooks(doom, ev);;
		//	printf("11\n");
		calc_mouse(&doom->player, doom->player.yaw);;
		//printf("12\n");
		calc_move(doom, &doom->player);;
		//printf("13\n");
		SDL_UpdateWindowSurface(doom->sdl->win);
		if (doom->a)
			doom->a = 0;
	}
	return (0);
}
