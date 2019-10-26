/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadgame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 18:13:26 by dtoy              #+#    #+#             */
/*   activedated: 2019/10/13 17:10:03 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		init_sdl(t_sdl *sdl)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	SDL_Surface	*surface;
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
	player->yaw = clamp(yaw + y * 0.01f, -5, 5);
	player->angle += x * 0.003f;
	player->psin = sinf(player->angle);
	player->pcos = cosf(player->angle);
	return (0);
}

void	change_move_vec(float *move_vec, t_player *player, float speed, char c)
{
	if (c == '+')
	{
		move_vec[0] += player->pcos * speed;
		move_vec[1] += player->psin * speed;
	}
	else
	{
		move_vec[0] -= player->pcos * speed;
		move_vec[1] -= player->psin * speed;
	}
}

int		direction(t_doom *doom, t_player *player, float *move_vec, t_fps fps)
{	
	float	speed;

	speed = player->sprint ? 0.7f : 0.4f;
	if (doom->wsad[0])
		change_move_vec(move_vec, player, speed, '+');
    if (doom->wsad[1])
		change_move_vec(move_vec, player, speed, '-');
    if (doom->wsad[2])
	{
		move_vec[0] += player->psin * speed;
		move_vec[1] -= player->pcos * speed;
	}
    if (doom->wsad[3])
	{
		move_vec[0] -= player->psin * speed;
		move_vec[1] += player->pcos * speed;
	}
	move_vec[0] *= fps.time_frame * 60.f;
	move_vec[1] *= fps.time_frame * 60.f;
	return (0);
}

int		calc_move(t_doom *doom, t_player *player)
{
	float move_vec[2] = {0.f, 0.f};
	float acceleration;

	if (player->dead)
		return (0);
	direction(doom, player, move_vec, doom->fps);
	doom->push = doom->wsad[0] || doom->wsad[1] || doom->wsad[2] || doom->wsad[3];
	acceleration = doom->push ? 0.6 : 0.4;
	player->velocity.x = player->velocity.x * (1 - acceleration) + move_vec[0] * acceleration;
	player->velocity.y = player->velocity.y * (1 - acceleration) + move_vec[1] * acceleration;
	if (doom->push == 1)
		player->move = 1;
	return (0);
}

int		calcnewsector(float dx, float dy, t_doom *doom, t_player *player)
{
	int		n;
	t_xy	p;
	t_sectors *sect;
	t_xy	*v;
	t_xy	delta;

	p.x = player->where.x;
	p.y = player->where.y;
	sect = &doom->sectors[player->sector];
	v = sect->vert;
	n = 0;
	while (n < sect->npoints)
	{
		if (sect->neighbors[n] >= 0 &&
		IntersectBox(p.x, p.y, p.x + dx, p.y + dy, v[n].x, v[n].y, v[n + 1].x, v[n + 1].y) &&
		PointSide(p.x + dx, p.y + dy, v[n].x, v[n].y, v[n + 1].x, v[n + 1].y) < 0)
		{
			player->sector = sect->neighbors[n];
			if (player->where.z != doom->sectors[player->sector].floor)
				doom->player.fall = 1;
			break ;
		}
		n++;
	}
	delta.x = dx;
	delta.y = dy;
	//player_move(doom, delta);
	doom->player.where.x += dx;
	doom->player.where.y += dy;
	doom->player.psin = sinf(doom->player.angle);
	doom->player.pcos = cosf(doom->player.angle);
	return (0);
}

int		calciswall(t_doom *doom, t_player *player)
{
	t_sectors *sect;
	t_xy	*v;
	float	px = player->where.x;
	float	py = player->where.y;
	float	dx = player->velocity.x;
	float	dy = player->velocity.y;
	float	hole_low;
	float	hole_high;
	float	xd, yd;
	int		n;
	float	tmp;
	int		t = 0;


	n = 0;
	sect = &doom->sectors[player->sector];
	v = sect->vert;
	//под вопросом 
/*	while (n < sect->npoints)
	{
	 	if (PointSide(px + dx, py + dy, v[n].x, v[n].y, v[n + 1].x, v[n + 1].y) < 0)
			t++;
	 	if (t == sect->npoints - 2)
	 		return (0);
	 	n++;
	}*/
	tmp = player->sit ? DuckHeight : EyeHeight;
	n = 0;
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
            || hole_low > player->where.z - tmp + KneeHeight)
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
	calcnewsector(dx, dy, doom, player);
	return (0);
}

void	player_on_ground(t_player *player, t_sectors *s, float height)
{
	player->where.z    = s->floor + height;
    player->velocity.z = 0;
    player->fall = 0;
    player->ground  = 1;
}

int		calc_jump(t_doom *doom, t_player *player, t_sectors *sectors, t_fps fps)
{
	float 	nextz;
	float	height;

	height = player->sit ? DuckHeight : EyeHeight;
	player->ground = !player->fall;
	if (player->fall)
	{
		player->velocity.z -= fps.time_frame * 5.f;
		nextz = player->where.z + player->velocity.z;
        if (player->velocity.z < 0 && nextz  < sectors[player->sector].floor + height)
			player_on_ground(player, &sectors[player->sector], height);
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

int		animation(t_doom *doom, t_fps fps)
{
	static float	t = 0;

	t += fps.time_frame;
	if (t >= 0.15f)
	{
		doom->a = 1;
		t = 0;
	}
	return (0);
}

void	close_door(t_sectors *s, t_fps fps)
{
	s->ceil -= fps.time_frame * 120.f;
	if (s->ceil <= s->floor)
	{
		s->ceil = s->floor;
		s->active = 0;
		s->open = 0;
		s->close = 1;
	}
}

void	open_door(t_sectors *s, t_fps fps)
{
	s->ceil += fps.time_frame * 120.f;
	if (s->ceil >= s->constceil)
	{
		s->ceil = s->constceil;
		s->active = 0;
		s->open = 1;
		s->close = 0;
	}
}

int		open_door_timer(t_sectors *s, t_fps fps)
{
	static float t = 0;

	if (s->open)
	{
		t += fps.time_frame;
		if (t >= 1.5f)
		{
			t = 0;
			return (1);
		}	
	}
	return (0);
}

int		doors(t_doom *doom, t_player player, t_fps fps)
{
	int		j;
	int		a;
	t_sectors *s;
	
	j = 0;
	a = 0;
	while (j < doom->num.sectors)
	{
		s = &doom->sectors[j];
		if ((open_door_timer(s, fps)))
			a = 1;
		if (s->open && a == 1)
			s->active = 1;
		if (s->active && j == player.sector && s->open)
			return (0);
		if ((s->type == 1 || (s->type == 2 && player.key)) && s->active && s->open)
			close_door(s, fps);
		else if ((s->type == 1 || (s->type == 2 && player.key)) && s->active && s->close)
			open_door(s, fps);
		j++;
	}
	return (0);
}

int		load_game(t_doom *doom)
{
	SDL_Event	ev;

	init_sdl(doom->sdl);
	loadfonts(doom->hud);
	load_hud(doom);
	while (1)
	{
		fps(&doom->fps);
		animation(doom, doom->fps);
		doors(doom, doom->player, doom->fps);
		draw_screen(doom);
		objects_update(doom);
		enemies_update(doom);
		player_blood_update(doom);
		calc_jump(doom, &doom->player, doom->sectors, doom->fps);
		if (doom->player.move == 1)
			calciswall(doom, &doom->player);
		while (SDL_PollEvent(&ev))
			hooks(doom, ev);
		calc_mouse(&doom->player, doom->player.yaw);
		calc_move(doom, &doom->player);
		SDL_UpdateWindowSurface(doom->sdl->win);
		if (doom->a)
			doom->a = 0;
	}
	return (0);
}
