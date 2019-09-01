/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawgame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 19:36:14 by dtoy              #+#    #+#             */
/*   Updated: 2019/09/01 19:13:16 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

struct xyz1
{
	float	x, y, z;
} t1, t2;

struct ab
{
	float	a, b;
} y, cy;

struct ab1
{
	int	a, b;
} yw1, yw2;

struct xy1
{
	float	x, y;
} v1, v2, i1, i2;

struct xy2
{
	int	x, y;
	int	ya, yb;
} w1, w2, w, c;


int			findintersect(struct xyz1 t1, struct xyz1 t2)
{	
	float nearz = 1e-4f, farz = 5, nearside = 1e-5f, farside = 20.f;
	
	i1 = Intersect(t1.x,t1.z,t2.x,t2.z, -nearside,nearz, -farside,farz);
    i2 = Intersect(t1.x,t1.z,t2.x,t2.z,  nearside,nearz,  farside,farz);
    if (t1.z < nearz)
	{ 
		if(i1.y > 0)
		{
			t1.x = i1.x;
			t1.z = i1.y;
		}
		else
		{
			t1.x = i2.x;
			t1.z = i2.y;
		}
	}
    if (t2.z < nearz)
	{
		if (i1.y > 0)
		{
			t2.x = i1.x;
			t2.z = i1.y;
		}
		else
		{
			t2.x = i2.x;
			t2.z = i2.y;
		} 
	}
	return (0);
}

int			nline(int x1, int y1, int x2, int y2, int color, t_sdl *sdl)
{
	sdl->line->x0 = x1;
	sdl->line->y0 = y1;
	sdl->line->x1 = x2;
	sdl->line->y1 = y2;
	sdl->line->color = color;
	line(sdl);
	return (0);
}

void		vline(int x, int y1,int y2, int top,int middle,int bottom, t_sdl *sdl)
{
	int		y;

    y1 = clamp(y1, 0, HEIGHT - 1);
    y2 = clamp(y2, 0, HEIGHT - 1);
    if(y2 == y1)
        sdl->pix[y1*WIDTH+x] = middle;
    else if(y2 > y1)
    {
        sdl->pix[y1*WIDTH+x] = top;
		y = y1 + 1;
        while (y < y2)
		{
			sdl->pix[y*WIDTH+x] = middle;
			y++;
		}
        sdl->pix[y2*WIDTH+x] = bottom;
    }
}

int			drawgame(t_doom *doom, t_player *player)
{
	t_sector *sect;
	float	xscale1, xscale2;
	float	yscale1, yscale2;
	float	yceil, yfloor;
	int		n;
	int		beginx, endx;
	int		ytop[WIDTH] = {0};
	int		ybot[WIDTH];
	float nearz = 1e-4f, farz = 5, nearside = 1e-5f, farside = 20.f;
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		ybot[x] = HEIGHT - 1;
		x++;
	}
	sect = &doom->sectors[player->sector];
	n = 0;
	again:
	while (n < sect->npoints)
	{
		v1.x = sect->vertex[n + 0].x - player->where.x;
		v1.y = sect->vertex[n + 0].y - player->where.y;
		v2.x = sect->vertex[n + 1].x - player->where.x;
		v2.y = sect->vertex[n + 1].y - player->where.y;
		t1.x = v1.x * player->anglesin - v1.y * player->anglecos;
		t1.z = v1.x * player->anglecos + v1.y * player->anglesin;
		t2.x = v2.x * player->anglesin - v2.y * player->anglecos;
		t2.z = v2.x * player->anglecos + v2.y * player->anglesin;
		if (t1.z <= 0 && t2.z <= 0) //стена за спиной
		{
			n++;
			goto again;
		}
		if (t1.z <= 0 || t2.z <= 0)
		{
			i1 = Intersect(t1.x,t1.z,t2.x,t2.z, -nearside,nearz, -farside,farz);
			i2 = Intersect(t1.x,t1.z,t2.x,t2.z,  nearside,nearz,  farside,farz);
			if (t1.z < nearz)
			{ 
				if(i1.y > 0)
				{
					t1.x = i1.x;
					t1.z = i1.y;
				}
				else
				{
					t1.x = i2.x;
					t1.z = i2.y;
				}
			}
			if (t2.z < nearz)
			{
				if (i1.y > 0)
				{
					t2.x = i1.x;
					t2.z = i1.y;
				}
				else
				{
					t2.x = i2.x;
					t2.z = i2.y;
				}
			}
		}
		
		xscale1 = hfov / t1.z;
		yscale1 = vfov / t1.z;
		xscale2 = hfov / t2.z;
		yscale2 = vfov / t2.z;
		w1.x = WIDTH / 2 - (int)(t1.x * xscale1);
		w2.x = WIDTH / 2 - (int)(t2.x * xscale2);
		if(w1.x >= w2.x || w2.x < 0 || w1.x > WIDTH - 1)
		{
			n++;
			goto again;
		}
		yceil  = sect->ceil  - player->where.z;
        yfloor = sect->floor - player->where.z;
		w1.ya = HEIGHT / 2 - (int)(yceil * yscale1);
		w1.yb = HEIGHT / 2 - (int)(yfloor * yscale1);
        w2.ya = HEIGHT / 2 - (int)(yceil * yscale2);
		w2.yb = HEIGHT / 2 - (int)(yfloor * yscale2);
		beginx = max(w1.x, 0);
		endx = min(w2.x, WIDTH - 1);
		x = beginx;
		while (x <= endx) //отрисовка
		{
			w.ya = (x - w1.x) * (w2.ya - w1.ya) / (w2.x - w1.x) + w1.ya;
			c.ya = clamp(w.ya, ytop[x], ybot[x]);
			w.yb = (x - w1.x) * (w2.yb - w1.yb) / (w2.x - w1.x) + w1.yb;
			c.yb = clamp(w.yb, ytop[x], ybot[x]);
			vline(x, ytop[x], c.ya - 1, 0x22222, 0x222222, 0x222222, doom->sdl); //потолок
			vline(x, c.yb + 1, ybot[x], 0xFF0000, 0x222222, 0, doom->sdl); //пол
			vline(x, c.ya, c.yb, 0xFF1010, (n + 1) * 0xFF5090, 0xFF1010, doom->sdl); //стена
			x++;
		}
		n++;
	}
	return (0);
}