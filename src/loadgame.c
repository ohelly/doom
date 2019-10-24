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

	SDL_GetRelativeMouseState(&x, &y);
	player->yaw = clamp(yaw + y * 0.01f, -5, 5);
	player->angle += x * 0.003f;
	player->psin = sinf(player->angle);
	player->pcos = cosf(player->angle);
	return (0);
}

int		direction(t_doom *doom, t_player *player, float *move_vec, t_fps fps)
{	
	if (doom->wsad[0])
	{
		move_vec[0] += player->pcos * 0.4f;
		move_vec[1] += player->psin * 0.4f;
	}
    if (doom->wsad[1])
	{
		move_vec[0] -= player->pcos * 0.4f;
		move_vec[1] -= player->psin * 0.4f;
	}
    if (doom->wsad[2])
	{
		move_vec[0] += player->psin * 0.4f;
		move_vec[1] -= player->pcos * 0.4f;
	}
    if (doom->wsad[3])
	{
		move_vec[0] -= player->psin * 0.4f;
		move_vec[1] += player->pcos * 0.4f;
	}
	move_vec[0] *= fps.time_frame * 60.f;
	move_vec[1] *= fps.time_frame * 60.f;
	return (0);
}

int		calc_move(t_doom *doom, t_player *player)
{
	float move_vec[2] = {0.f, 0.f};
	float acceleration;

	direction(doom, player, move_vec, doom->fps);
	doom->push = doom->wsad[0] || doom->wsad[1] || doom->wsad[2] || doom->wsad[3];
	acceleration = doom->push ? 0.6 : 0.4;
	player->velocity.x = player->velocity.x * (1 - acceleration) + move_vec[0] * acceleration;
	player->velocity.y = player->velocity.y * (1 - acceleration) + move_vec[1] * acceleration;
	if (doom->push == 1)
		player->move = 1;
	//printf("x - %f, y - %f\n", player->velocity.x, player->velocity.y);
	// if (!player->velocity.x && !player->velocity.y)
	// 	player->move = 0;
	return (0);
}

int		calcnewsector(float dx, float dy, t_doom *doom, t_player *player)
{
	int		n;
	float	px, py;
	t_sectors *sect;
	t_xy	*v;

	px = player->where.x;
	py = player->where.y;
	sect = &doom->sectors[player->sector];
	v = sect->vert;
	n = 0;
	while (n < sect->npoints)
	{
		if (sect->neighbors[n] >= 0 &&
		IntersectBox(px, py, px + dx, py + dy, v[n].x, v[n].y, v[n + 1].x, v[n + 1].y) &&
		PointSide(px + dx, py + dy, v[n].x, v[n].y, v[n + 1].x, v[n + 1].y) < 0)
		{
			player->sector = sect->neighbors[n];
			if (player->where.z != doom->sectors[player->sector].floor)
				doom->player.fall = 1;
			break ;
		}
		n++;
	}
	player_move(doom, (t_xy){dx, dy});
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
	int		t = 0;

	n = 0;
	sect = &doom->sectors[player->sector];
	v = sect->vert;
	while (n < sect->npoints)
	{
		if (PointSide(px + dx, py + dy, v[n].x, v[n].y, v[n + 1].x, v[n + 1].y) < 0)
			t++;
		if (t >= 2)
			return (0);
		n++;
	}
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
	calcnewsector(dx, dy, doom, player);
	return (0);
}

int		calc_jump(t_doom *doom, t_player *player, t_sectors *sectors, t_fps fps)
{
	float 	nextz;

	player->ground = !player->fall;
	if (player->fall)
	{
		player->velocity.z -= fps.time_frame * 5.f;
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

int		doors(t_doom *doom, t_player player, t_fps fps)
{
	int		n;
	int		neigh;
	int		j;
	int		a = 0;
	static float t = 0;
	t_sectors *s;
	
	j = 0;
	while (j < doom->num.sectors)
	{
		s = &doom->sectors[j];
		if (s->open)
		{
			t += fps.time_frame;
			if (t >= 1.5f)
			{
				a = 1;
				t = 0;
			}	
		}
		if (s->open && a == 1)
			s->active = 1;
		if (s->active && j == player.sector && s->open)
			return (0);
		if (s->type == 1 && s->active && s->open)
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
		else if (s->type == 1 && s->active && s->close)
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
		
		//enemies_activedate(doom);
		animation(doom, doom->fps);
		doors(doom, doom->player, doom->fps);
		draw_screen(doom);
		if (doom->lkey == 1 && doom->player.weapon == 3 && doom->weapon[doom->player.weapon].ammo > 0 && doom->weapon[doom->player.weapon].anim_frame % 3 == 0) //временно
		{
			
			doom->weapon[doom->player.weapon].ammo--;
			shoot(doom);
		}
		objects_update(doom);
		enemies_update(doom);
		player_blood_update(doom);
		calc_jump(doom, &doom->player, doom->sectors, doom->fps);
		if (doom->player.move == 1)
			calciswall(doom, &doom->player);
		while (SDL_PollEvent(&ev))
		{
			hooks(doom, ev);
		}
		calc_mouse(&doom->player, doom->player.yaw);
		calc_move(doom, &doom->player);
		SDL_UpdateWindowSurface(doom->sdl->win);
		if (doom->a)
			doom->a = 0;
	}
	return (0);
}

/*
int		initsdl(t_doom *doom, t_sdl *sdl)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Surface	*surface;
	sdl->win = SDL_CreateWindow("Doom", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	surface = SDL_GetWindowSurface(sdl->win);
	sdl->pix = (int*)surface->pixels;
	doom->player.fall = 0;
	SDL_SetRelativeMouseMode(1);
	return (0);
}

int		calcmouse(t_player *player, float yaw)
{
	int		x;
	int		y;

	SDL_GetRelativeMouseState(&x, &y);
	player->yaw = clamp(yaw + y * 0.01f, -5, 5);
	player->angle += x * 0.003f;
	// if (player->angle > 6.283184)
	// 	player->angle -= 6.283184;
	// else if (player->angle < -6.283184)
	// 	player->angle += 6.283184;
	player->psin = sinf(player->angle);
	player->pcos = cosf(player->angle);
	return (0);
}

int		direction(t_doom *doom, t_player *player, float *move_vec)
{	
	if (doom->wsad[0])
	{
		move_vec[0] += player->pcos * 0.4f;
		move_vec[1] += player->psin * 0.4f;
	}
    if (doom->wsad[1])
	{
		move_vec[0] -= player->pcos * 0.4f;
		move_vec[1] -= player->psin * 0.4f;
	}
    if (doom->wsad[2])
	{
		move_vec[0] += player->psin * 0.4f;
		move_vec[1] -= player->pcos * 0.4f;
	}
    if (doom->wsad[3])
	{
		move_vec[0] -= player->psin * 0.4f;
		move_vec[1] += player->pcos * 0.4f;
	}
	move_vec[0] *= doom->time_frame * 60;
	move_vec[1] *= doom->time_frame * 60;
	return (0);
}

int		calcmove(t_doom *doom, t_player *player)
{
	float move_vec[2] = {0.f, 0.f};
	float acceleration;

	direction(doom, player, move_vec);
	doom->push = doom->wsad[0] || doom->wsad[1] || doom->wsad[2] || doom->wsad[3];
	acceleration = doom->push ? 0.6 : 0.4;
	player->velocity.x = player->velocity.x * (1 - acceleration) + move_vec[0] * acceleration;
	player->velocity.y = player->velocity.y * (1 - acceleration) + move_vec[1] * acceleration;
	if (doom->push == 1)
		player->move = 1;
	return (0);
}

int		overlap(float a0, float a1, float b0, float b1)
{
	return (min(a0,a1) <= max(b0,b1) && min(b0,b1) <= max(a0,a1));
}

int		pointside(t_xy p, t_xy d, t_xy v1, t_xy v2)
{
	return (vxs(v1.x - (p.x + d.x), v1.y - (p.y + d.y), p.x - (p.x + d.x), p.y - (p.y + d.y)));
}

int		calcnewsector(float dx, float dy, t_doom *doom, t_player *player)
{
	int			n;
	t_xy		p;
	t_xy		d;
	t_sector	*sect;
	t_xy		*v;

	p = (t_xy){player->where.x, player->where.y};
	d = (t_xy){dx, dy};
	sect = &doom->sector[player->sector];
	v = sect->vert;
	n = 0;
	while (n < sect->npoints)
	{
		if (sect->neighbors[n] >= 0 &&
			collision_box_dir(p, v2_add(p, d), v[n], v[n + 1]))
		{
			player->sector = sect->neighbors[n];
			if (player->where.z != doom->sector[player->sector].floor)
				doom->player.fall = 1;
			break ;
		}
		n++;
	}

	player_move(doom, (t_xy){d.x, d.y});

	/*
	player->where.x += dx;
	player->where.y += dy;
	player->psin = sinf(player->angle);
	player->pcos = cosf(player->angle);
	return (0);
}

int		calciswall(t_doom *doom, t_player *player)
{
	t_sector *sect;
	t_xy	*v;
	t_xy	p = (t_xy){player->where.x, player->where.y};
	t_xy	d = (t_xy){player->velocity.x, player->velocity.y};
	float	hole_low;
	float	hole_high;
	float	xd, yd;
	int		n;
	int		t = 0;

	n = 0;
	sect = &doom->sector[player->sector];
	v = sect->vert;
	while (n < sect->npoints)
	{
		if (PointSide(p.x + d.x * 8.0f, p.y + d.y * 8.0f, v[n].x, v[n].y, v[n + 1].x, v[n + 1].y) < 0)
			t++;
		if (t >= 2)
			return (0);
		n++;
	}
	n = 0;
	while (n < sect->npoints)
	{
		if (collision_box_dir(p, v2_add(p, v2_multf(d, 8.0f)), v[n], v[n + 1]))
		{
			player->velocity.x = 0;
			player->velocity.y = 0;
			hole_low  = sect->neighbors[n] < 0 ?  9e9 : max(sect->floor, doom->sector[sect->neighbors[n]].floor);
			hole_high = sect->neighbors[n] < 0 ? -9e9 : min(sect->ceil,  doom->sector[sect->neighbors[n]].ceil);
			if (hole_high < player->where.z + HeadMargin ||
				hole_low  > player->where.z - EyeHeight + KneeHeight)
			{
				xd = v[n + 1].x - v[n].x + (d.x * -8.0f);
				yd = v[n + 1].y - v[n].y + (d.y * -8.0f);
				d.x = xd * (d.x * xd + yd * d.y) / (xd * xd + yd * yd);
				d.y = yd * (d.x * xd + yd * d.y) / (xd * xd + yd * yd);
				break ;
			}
		}
		n++;
	}
	calcnewsector(d.x, d.y, doom, player);
	return (0);
}

int		calcjump(t_doom *doom, t_player *player, t_sector *sectors)
{
	float 	nextz;

	player->ground = !player->fall;
	if (player->fall)
	{
		player->velocity.z -= doom->time_frame * 5.f;
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

int		fps(t_doom *doom)
{
	doom->times[1] = doom->times[0];
	doom->times[0] = SDL_GetTicks();
	doom->time_frame = (doom->times[0] - doom->times[1]) / 1000;
	doom->time_fps_count++;
	doom->time_fps_total += doom->time_frame;
	//printf("fps_count %f, fps total %f\n", doom->time_fps_count, doom->time_fps_total);
	
	return (0);
}

int		animation(t_doom *doom)
{
	static float	t = 0;

	t += doom->time_frame;
	if (t >= 0.15f)
	{
		doom->a = 1;
		t = 0;
	}	
	return (0);
}

int		types(t_doom *doom, t_player player)
{
	int		n;
	int		neigh;
	int		j;
	int		a = 0;
	static float t = 0;
	t_sector *s;
	
	j = 0;
	while (j < doom->numsectors)
	{
		s = &doom->sector[j];
		if (s->open)
		{
			t += doom->time_frame;
			if (t >= 1.5f)
			{
				a = 1;
				t = 0;
			}	
		}
		if (s->open && a == 1)
			s->active = 1;
		if (s->active && j == player.sector && s->open)
			return (0);
		if (s->type && s->active && s->open)
		{
			s->ceil -= doom->time_frame * 120.f;
			if (s->ceil <= s->floor)
			{
				s->ceil = s->floor;
				s->active = 0;
				s->open = 0;
				s->close = 1;
			}
		}
		else if (s->type && s->active && s->close)
		{
			s->ceil += doom->time_frame * 120.f;
			if (s->ceil >= s->tmpceil)
			{
				s->ceil = s->tmpceil;
				s->active = 0;
				s->open = 1;
				s->close = 0;
			}
		}
		j++;
	}
	return (0);
}

int		loadgame(t_doom *doom)
{
	SDL_Event	ev;

	initsdl(doom, doom->sdl);
	while (1)
	{	
		fps(doom);
		types(doom, doom->player);
		enemies_activedate(doom);
		animation(doom);
		drawscreen(doom);
		calcjump(doom, &doom->player, doom->sector);
		if (doom->player.move == 1)
			calciswall(doom, &doom->player);
		while(SDL_PollEvent(&ev))
			hooks(doom, ev);
		calcmouse(&doom->player, doom->player.yaw);
		calcmove(doom, &doom->player);
		SDL_memset(doom->sdl->pix, 0, WIDTH * 4);
		SDL_activedateWindowSurface(doom->sdl->win);
		if (doom->a)
			doom->a = 0;
	}
	return (0);
}
*/
