/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdlstart.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 19:28:15 by dtoy              #+#    #+#             */
/*   Updated: 2019/09/01 19:30:54 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int     sdlstart(t_doom *doom)
{   
    SDL_Event   ev;
    int x,y;

    SDL_Init(SDL_INIT_EVERYTHING);
    doom->sdl->win = SDL_CreateWindow("Doom", 200, 200, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    doom->sdl->surface = SDL_GetWindowSurface(doom->sdl->win);
    doom->sdl->pix = (int*)doom->sdl->surface->pixels;
    while (1)
    {
        SDL_LockSurface(doom->sdl->surface);
		drawgame(doom, doom->player);
		SDL_UnlockSurface(doom->sdl->surface);
		SDL_SetRelativeMouseMode(1);
      	SDL_GetRelativeMouseState(&x,&y);
      	doom->player->angle += x * 0.005f;
        doom->player->anglesin = sinf(doom->player->angle);
        doom->player->anglecos = cosf(doom->player->angle);
        while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_KEYDOWN)
            {
		        if (ev.key.keysym.sym == '\033')
			    {
			    	SDL_Quit();
			    	exit(0);
			    }
			    if (ev.key.keysym.sym == 'w')
			    {
			    	doom->player->where.x = doom->player->where.x + doom->player->anglecos;
			    	doom->player->where.y = doom->player->where.y + doom->player->anglesin;
			    }
			    if (ev.key.keysym.sym == 's')
			    {
			    	doom->player->where.x = doom->player->where.x - doom->player->anglecos;
			    	doom->player->where.y = doom->player->where.y - doom->player->anglesin;
			    }
			    if (ev.key.keysym.sym == 'a')
			    {
			    	doom->player->where.x = doom->player->where.x + doom->player->anglesin;
			    	doom->player->where.y = doom->player->where.y - doom->player->anglecos;
			    }
			    if (ev.key.keysym.sym == 'd')
			    {
			    	doom->player->where.x = doom->player->where.x - doom->player->anglesin;
			    	doom->player->where.y = doom->player->where.y + doom->player->anglecos;
			    }
			    if (ev.key.keysym.sym == SDLK_LEFT)
			    	doom->player->angle -= 5;
			    if (ev.key.keysym.sym == SDLK_RIGHT)
			    	doom->player->angle += 5;
            }
        }
		SDL_UpdateWindowSurface(doom->sdl->win);
		SDL_Delay(10);
		SDL_memset(doom->sdl->pix, 0, WIDTH * HEIGHT * 4); 
	}
	return (0);
}
