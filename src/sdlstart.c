/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdlstart.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 19:28:15 by dtoy              #+#    #+#             */
/*   Updated: 2019/09/13 19:02:13 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "doom.h"

int		newsector(float dx, float dy, t_doom *doom, t_player *player)
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
				doom->fall = 1;
			break ;
		}
		n++;
	}
	player->where.x += dx;
	player->where.y += dy;
	player->anglesin = sinf(player->angle);
	player->anglecos = cosf(player->angle);
	printf("Now sector - %d\n", player->sector);
	return (0);
}

int		isitwall(t_doom *doom, t_player *player)
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
	int		t = 0;

	n = 0;
	sect = &doom->sectors[player->sector];
	v = sect->vertex;
	//printf("Player Sector - %d\n", player->sector);
	while (n < sect->npoints)
	{
		if (t >= 1)
		{
			player->where.x = px;
			player->where.y = py;
			doom->move = 0;
			return (0);
		}
		if ((sect->neighbors[n] == -1) && PointSide(px + dx, py + dy, v[n].x, v[n].y, v[n + 1].x, v[n + 1].y) < 0)
			t++;
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
	newsector(dx, dy, doom, doom->player);
	return (0);
}

int 	moving(t_doom *doom, t_player *player)
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
	if (doom->stop == 0)
	{
	    player->velocity.x = player->velocity.x * (1-acceleration) + move_vec[0] * acceleration;
	    player->velocity.y = player->velocity.y * (1-acceleration) + move_vec[1] * acceleration;
	}
	else
	{
		player->velocity.x = 0;
		player->velocity.y = 0;
		doom->stop = 0;
	}
	if (doom->push == 1)
		doom->move = 1;
	return (0);
}

int		mouse(t_player *player, float yaw)
{
	int		x, y;

	SDL_GetRelativeMouseState(&x, &y);
	yaw = clamp(yaw + y * 0.01f, -5, 5);
	player->yaw = yaw;
	player->angle += x * 0.005f;
	return (0);
}

int		drawweapon(t_doom *doom)
{
	SDL_RenderClear(doom->sdl->img->ren);
	SDL_RenderCopy(doom->sdl->img->ren, doom->sdl->img->minigun_tex, NULL, NULL);
	SDL_RenderPresent(doom->sdl->img->ren);
	return (0);
}

int     sdlstart(t_doom *doom)
{
	float		gravity = -0.3f;
	float nextz;

	SDL_Event	ev;
	SDL_Init(SDL_INIT_EVERYTHING);
	ft_memset(doom->wsad, 0, 4 * 4);
	doom->sdl->win = SDL_CreateWindow("Doom", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	doom->sdl->surface = SDL_GetWindowSurface(doom->sdl->win);
	doom->sdl->pix = (int*)doom->sdl->surface->pixels;
	doom->fall = 0;
	SDL_FreeSurface(doom->sdl->img->minigun);
	doom->player->where.z = doom->sectors[doom->player->sector].floor + EyeHeight;
	while (1)
	{
		
		printf("vz - %f\n", doom->player->velocity.z);
		SDL_LockSurface(doom->sdl->surface);
		drawgame(doom, doom->player);
		//drawweapon(doom);
		SDL_UnlockSurface(doom->sdl->surface);
		SDL_SetRelativeMouseMode(1);
		doom->ground = !doom->fall;
		if (doom->fall)
		{
			doom->player->velocity.z -= 0.05f;
			nextz = doom->player->where.z + doom->player->velocity.z;
            if (doom->player->velocity.z < 0 && nextz  < doom->sectors[doom->player->sector].floor + EyeHeight)
            {
                doom->player->where.z    = doom->sectors[doom->player->sector].floor + EyeHeight;
                doom->player->velocity.z = 0;
                doom->fall = 0;
                doom->ground  = 1;
            }
            else if (doom->player->velocity.z > 0 && nextz > doom->sectors[doom->player->sector].ceil)
            {
                doom->player->velocity.z = 0;
                doom->fall = 1;
            }
            if (doom->fall)
            {
                doom->player->where.z += doom->player->velocity.z;
                doom->move = 1;
            }
		}
		
		if (doom->move == 1)
			isitwall(doom, doom->player);
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
					doom->wsad[0] = 1;
				if (ev.key.keysym.sym == 's')
					doom->wsad[1] = 1;
				if (ev.key.keysym.sym == 'a')
					doom->wsad[2] = 1;
				if (ev.key.keysym.sym == 'd')
					doom->wsad[3] = 1;
				if (ev.key.keysym.sym == '0')
					doom->sectors[doom->player->sector].ceil -= 1;
				if (ev.key.keysym.sym == '9')
					doom->sectors[doom->player->sector].ceil += 1;
				if (ev.key.keysym.sym == '=')
					doom->sectors[doom->player->sector].floor += 1;
				if (ev.key.keysym.sym == '-')
					doom->sectors[doom->player->sector].floor -= 1;
				if (ev.key.keysym.sym == SDLK_SPACE)
				{
					if (doom->ground)
					{
						doom->player->velocity.z = 1.5;
						doom->fall = 1;
					}
				}
				if (ev.key.keysym.sym == SDLK_LCTRL)
					doom->duck = 1;
				if (ev.key.keysym.sym == SDLK_LSHIFT)
					doom->sprint = 1;
				break ;
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
				if (ev.key.keysym.sym == SDLK_LCTRL)
					doom->duck = 0;
				if (ev.key.keysym.sym == SDLK_LSHIFT)
					doom->sprint = 0;
				break ;
			}	
		}
		mouse(doom->player, doom->player->yaw);
		newsector(0, 0, doom, doom->player);
		moving(doom, doom->player);
		SDL_UpdateWindowSurface(doom->sdl->win);
		SDL_memset(doom->sdl->pix, 0, WIDTH * HEIGHT * 4);
		SDL_Delay(10);
	}
	return (0);
}
