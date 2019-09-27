/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 15:29:03 by dtoy              #+#    #+#             */
/*   Updated: 2019/09/27 17:36:24 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		init_sdl(t_doom *doom)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	doom->sdl->win = SDL_CreateWindow("Doom", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	doom->sdl->surface = SDL_GetWindowSurface(doom->sdl->win);
	doom->sdl->pix = (int*)doom->sdl->surface->pixels;
	ft_memset(doom->wsad, 0, 4 * 4);
	SDL_SetRelativeMouseMode(1);
	return (0);
}

int		calcjump(t_player *player, t_sector *sectors)
{
	float 	nextz;

	player->ground = !player->fall;
	if (player->fall)
	{
		player->velocity.z -= 0.05f;
		nextz = player->where.z + player->velocity.z;
        if (player->velocity.z < 0 && nextz  < sectors[player->sector].floor + EyeHeight)
        {
            player->where.z    = sectors[player->sector].floor + EyeHeight;
            player->velocity.z = 0;
            player->fall = 0;
            player->ground  = 1;
        }
        else if (player->velocity.z > 0 && nextz > sectors[player->sector].ceil)
        {
            player->velocity.z = 0;
            player->fall = 1;
        }
        if (player->fall)
        {
            player->where.z += player->velocity.z;
            player->move = 1;
        }
	}
	return (0);
}

int		calchooks(t_doom *doom, SDL_Event ev)
{
	if (ev.type == SDL_KEYDOWN)
	{
		if (ev.key.keysym.sym == '\033')
		{
			SDL_Quit();
			exit(0);
		}
		if (ev.key.keysym.sym == 'w')
			doom->wsad[0] = 1;
		if (ev.key.keysym.sym == 's')
			doom->wsad[1] = 1;
		if (ev.key.keysym.sym == 'a')
			doom->wsad[2] = 1;
		if (ev.key.keysym.sym == 'd')
			doom->wsad[3] = 1;
		if (ev.key.keysym.sym == '0')
			doom->sectors[doom->player->sector].floor += 1;
		if (ev.key.keysym.sym == SDLK_SPACE)
		{
			if (doom->player->ground)
			{
				doom->player->velocity.z = 1.5;
				doom->player->fall = 1;
			}
		}	
	}
	if (ev.type == SDL_KEYUP)
	{
		if (ev.key.keysym.sym == 'w')
			doom->wsad[0] = 0;
		if (ev.key.keysym.sym == 's')
			doom->wsad[1] = 0;
		if (ev.key.keysym.sym == 'a')
			doom->wsad[2] = 0;
		if (ev.key.keysym.sym == 'd')
			doom->wsad[3] = 0;
	}
	return (0);
}

int		calcnewsector(float dx, float dy, t_doom *doom, t_player *player)
{
	int		n;
	float	px, py;
	t_sector *sect;
	t_xy	*v;

	px = player->where.x;
	py = player->where.y;
	sect = &doom->sectors[player->sector];
	v = sect->vertex;
	n = 0;
	while (n < sect->npoints)
	{
		if (sect->neighbors[n] >= 0 &&
		IntersectBox(px, py, px + dx, py + dy, v[n].x, v[n].y, v[n + 1].x, v[n + 1].y) &&
		PointSide(px + dx, py + dy, v[n].x, v[n].y, v[n + 1].x, v[n + 1].y) < 0)
		{
			player->sector = sect->neighbors[n];
			if (player->where.z != doom->sectors[player->sector].floor)
				doom->player->fall = 1;
			break ;
		}
		n++;
	}
	player->where.x += dx;
	player->where.y += dy;
	player->anglesin = sinf(player->angle);
	player->anglecos = cosf(player->angle);
//	printf("Now sector - %d\n", player->sector);
	return (0);
}

int		calciswall(t_doom *doom, t_player *player)
{
	t_sector *sect;
	t_xy	*v;
	float	px = player->where.x;
	float	py = player->where.y;
	float	dx = player->velocity.x;
	float	dy = player->velocity.y;
	float	hole_low;
	float	hole_high;
	float	xd, yd;
	int		n;

	n = 0;
	sect = &doom->sectors[player->sector];
	v = sect->vertex;
	while (n < sect->npoints)
	{
		if ((IntersectBox(px, py, px + dx, py + dy, v[n].x, v[n].y, v[n + 1].x, v[n + 1].y) &&
		PointSide(px + dx, py + dy, v[n].x, v[n].y, v[n + 1].x, v[n + 1].y) < 0))
		{
			player->velocity.x = 0;
			player->velocity.y = 0;
			hole_low  = sect->neighbors[n] < 0 ?  9e9 : max(sect->floor, doom->sectors[sect->neighbors[n]].floor);
            hole_high = sect->neighbors[n] < 0 ? -9e9 : min(sect->ceil,  doom->sectors[sect->neighbors[n]].ceil);
            if (hole_high < player->where.z + HeadMargin
            || hole_low  > player->where.z - EyeHeight + KneeHeight)
            {
				xd = v[n + 1].x - v[n].x;
				yd = v[n + 1].y - v[n].y;
           		dx = xd * (dx * xd + yd * dy) / (xd * xd + yd * yd);
           		dy = yd * (dx * xd + yd * dy) / (xd * xd + yd * yd);
				break ;
			}
		}
		n++;
	}
	calcnewsector(dx, dy, doom, doom->player);
	return (0);
}

int		calcmouse(t_player *player, float yaw)
{
	int		x;
	int		y;

	SDL_GetRelativeMouseState(&x, &y);
	yaw = clamp(yaw + y * 0.01f, -5, 5);
	player->yaw = yaw;
	player->angle += x * 0.003f;
	return (0);
}

int		calcmove(t_doom *doom, t_player *player)
{
	float move_vec[2] = {0.f, 0.f};
	float acceleration;

    if (doom->wsad[0])
	{
		move_vec[0] += player->anglecos * 0.4f;
		move_vec[1] += player->anglesin * 0.4f;
	}
    if (doom->wsad[1])
	{
		move_vec[0] -= player->anglecos * 0.4f;
		move_vec[1] -= player->anglesin * 0.4f;
	}
    if (doom->wsad[2])
	{
		move_vec[0] += player->anglesin * 0.4f;
		move_vec[1] -= player->anglecos * 0.4f;
	}
    if (doom->wsad[3])
	{
		move_vec[0] -= player->anglesin * 0.4f;
		move_vec[1] += player->anglecos * 0.4f;
	}
	doom->push = doom->wsad[0] || doom->wsad[1] || doom->wsad[2] || doom->wsad[3];
	acceleration = doom->push ? 0.6 : 0.4;
	player->velocity.x = player->velocity.x * (1-acceleration) + move_vec[0] * acceleration;
	player->velocity.y = player->velocity.y * (1-acceleration) + move_vec[1] * acceleration;
	if (doom->push == 1)
		doom->player->move = 1;
	return (0);
}

int		loadgame(t_doom *doom)
{
	SDL_Event	ev;
	int		t = 0;
	init_sdl(doom);
	doom->player->fall = 0;
	while (1)
	{
		if (t == 10)
		{
			doom->a++;
			t = 0;
		}
		if (doom->a == 6)
			doom->a = 0;
		t++;
		SDL_LockSurface(doom->sdl->surface);
		drawgame(doom, doom->player);
		SDL_UnlockSurface(doom->sdl->surface);
		calcjump(doom->player, doom->sectors);
		if (doom->player->move == 1)
			calciswall(doom, doom->player);
		while (SDL_PollEvent(&ev))
			calchooks(doom, ev);
		calcmouse(doom->player, doom->player->yaw);
		calcmove(doom, doom->player);
		SDL_UpdateWindowSurface(doom->sdl->win);
		SDL_memset(doom->sdl->pix, 0, WIDTH * HEIGHT * 4);
		SDL_Delay(10);
	}
	return (0);
}
