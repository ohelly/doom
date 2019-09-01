/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawgame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 19:36:14 by dtoy              #+#    #+#             */
/*   Updated: 2019/09/01 18:53:00 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
/*
int			findintersect(float *tx1, float *tz1, float *tx2, float *tz2)
{
	float nearz = 1e-4f, farz = 5, nearside = 1e-5f, farside = 20.f;
	t_xy i1 = Intersect(*tx1,*tz1,*tx2,*tz2, -nearside,nearz, -farside,farz);
    t_xy i2 = Intersect(*tx1,*tz1,*tx2,*tz2,  nearside,nearz,  farside,farz);
    if(*tz1 < nearz) { if(i1.y > 0) { *tx1 = i1.x; *tz1 = i1.y; } else { *tx1 = i2.x; *tz1 = i2.y; } }
    if(*tz2 < nearz) { if(i1.y > 0) { *tx2 = i1.x; *tz2 = i1.y; } else { *tx2 = i2.x; *tz2 = i2.y; } }
	return (0);
}

float		yaw(float y, float z, t_player *player)
{
	return (y + z * player->yaw);
}

void		vline(int x, int y1, int y2, int top, int middle, int bottom, t_sdl *sdl)
{
	int		 y;

	y1 = clamp(y1, 0, HEIGHT - 1);
	y2 = clamp(y2, 0, HEIGHT - 1);
	if (y1 == y2)
		sdl->sdl->pix[y1 * WIDTH + x] = middle;
	else if (y2 > y1)
	{
		sdl->sdl->pix[y1 * WIDTH + x] = top;
		y = y1 + 1;
		while (y < y2)
		{
			sdl->sdl->pix[y * WIDTH + x] = middle;
			y++;
		}
		sdl->sdl->pix[y2 * WIDTH + x] = bottom;
	}
}

int			drawgame(t_doom *doom, t_player *player)
{
	t_sector	*sect;
	//int			n;
	int			neighbor;
	float		vx1, vy1;
	float		vx2, vy2;
	float		tx1, tz1;
	float		tx2, tz2;
	float		pcos, psin;
	float		xscale1, yscale1;
	float		xscale2, yscale2;
	float		yceil, yfloor;
	float		nyceil, nyfloor;
	int			x1, x2, y1a, y2a, y1b, y2b;
	int			ny1a, ny1b;
	int			ny2a, ny2b;
	int			beginx, endx;
	int			x, ya, yb, z, cya, cyb;
	int			ytop[WIDTH] = {0}, ybottom[WIDTH];
	int			nya, nyb, cnya, cnyb;
	int			renderedsectors[doom->numsectors];
	int			MaxQueue = 32;  // maximum number of pending portal renders
    struct item {
		int sectorno,sx1,sx2;
	} queue[MaxQueue], *head=queue, *tail=queue;
	
 	for (unsigned i = 0; i < WIDTH; ++i)
		ybottom[i] = HEIGHT - 1;
 	for (unsigned n = 0; n < doom->numsectors; ++n)
	 	renderedsectors[n] = 0;

//     Begin whole-screen rendering from where the player is. 
    *head = (struct item) { player->sector, 0, WIDTH - 1 };
	//printf("head 1 - %d\n", head->sectorno);
    if(++head == queue+MaxQueue)
	head = queue;
	//printf("\n");
    while(head != tail) {
    //  Pick a sector & slice from the queue to draw 
	 
    struct item now = *tail;
    if(++tail == queue+MaxQueue)
		tail = queue;
	//printf("now - %d\n", now.sectorno);
    if(renderedsectors[now.sectorno] & 0x21) continue; // Odd = still rendering, 0x20 = give up
		++renderedsectors[now.sectorno];
	sect = &doom->sectors[now.sectorno];
	//printf("ren - %d\n", renderedsectors[now.sectorno] & 0x21);
	nyceil = 0;
	nyfloor = 0;
	int n = 0;
	again:
	while (n < sect->npoints)
	{
		vx1 = sect->vertex[n + 0].x - player->where.x;
		vy1 = sect->vertex[n + 0].y - player->where.y;
		vx2 = sect->vertex[n + 1].x - player->where.x;
		vy2 = sect->vertex[n + 1].y - player->where.y;
		pcos = player->anglecos;
		psin = player->anglesin;
		tx1 = vx1 * psin - vy1 * pcos;
		tz1 = vx1 * pcos + vy1 * psin;
		tx2 = vx2 * psin - vy2 * pcos;
		tz2 = vx2 * pcos + vy2 * psin;
		if (tz1 <= 0 && tz2 <= 0)
		{
			n++;
			goto again;
			//continue ;
		}
		if (tz1 <= 0 || tz2 <= 0)
			findintersect(&tx1, &tz1, &tx2, &tz2);
		xscale1 = hfov / tz1;
		yscale1 = vfov / tz1;
		xscale2 = hfov / tz2;
		yscale2 = vfov / tz2;
		x1 = WIDTH / 2 - (int)(tx1 * xscale1);
		x2 = WIDTH / 2 - (int)(tx2 * xscale2);
		if(x1 >= x2 || x2 < 0 || x1 > WIDTH - 1)
		{
			n++;
			goto again;
		//	continue ;
		}
		yceil  = sect->ceil  - player->where.z;
        yfloor = sect->floor - player->where.z;
		neighbor = sect->neighbors[n];
		if(neighbor >= 0) // Is another sector showing through this portal?
        {
            nyceil  = doom->sectors[neighbor].ceil  - player->where.z;
            nyfloor = doom->sectors[neighbor].floor - player->where.z;
        }
		y1a = HEIGHT / 2 - (int)(yceil * yscale1);
		y1b = HEIGHT / 2 - (int)(yfloor * yscale1);
        y2a = HEIGHT / 2 - (int)(yceil * yscale2);
		y2b = HEIGHT / 2 - (int)(yfloor * yscale2);
        ny1a = HEIGHT / 2 - (int)(nyceil * yscale1);
		ny1b = HEIGHT / 2 - (int)(nyfloor * yscale1);
        ny2a = HEIGHT / 2 - (int)(nyceil * yscale2);
		ny2b = HEIGHT / 2 - (int)(nyfloor * yscale2);
		beginx = max(x1, now.sx1);
		endx = min(x2, now.sx2);
		int x = beginx;
		while (x <= endx)
		{
			ya = (x - x1) * (y2a-y1a) / (x2-x1) + y1a;
			cya = clamp(ya, 0,HEIGHT - 1); // top
            yb = (x - x1) * (y2b-y1b) / (x2-x1) + y1b;
			cyb = clamp(yb, 0,HEIGHT - 1); // bottom	
			vline(x, 0, cya-1, 0x111111 ,0x222222,0x111111, doom->sdl);
			vline(x, cyb+1, HEIGHT - 1, 0x0000FF,0x0000AA,0x0000FF, doom->sdl);
			if (neighbor >= 0)
			{
				//printf("ytop - %d\n", 0);
				nya = (x - x1) * (ny2a-ny1a) / (x2-x1) + ny1a;
				cnya = clamp(nya, 0,HEIGHT - 1);
				nyb = (x - x1) * (ny2b-ny1b) / (x2-x1) + ny1b;
				cnyb = clamp(nyb, 0,HEIGHT - 1);
				vline(x, cya, cnya-1, 0, x == x1 || x == x2 ? 0 : 0xAAAAAA, 0, doom->sdl);
				0 = clamp(max(cya, cnya), 0, HEIGHT - 1);
    			vline(x, cnyb+1, cyb, 0, x == x1 || x == x2 ? 0 : 0x7C00D9, 0, doom->sdl);
    			HEIGHT - 1 = clamp(min(cyb, cnyb), 0, HEIGHT - 1);
				vline(x, cya, cyb, 0x00AA00, 0x00AA00, 0x00AA00, doom->sdl);
			}
			else
                vline(x, cya, cyb, 0, x == x1 || x == x2 ? 0 : 0xAAAAAA, 0, doom->sdl);
			x++;
		}
		if(neighbor >= 0 && endx >= beginx && (head+MaxQueue+1-tail)%MaxQueue)
        {
        	*head = (struct item) { neighbor, beginx, endx };
        	if(++head == queue+MaxQueue) head = queue;
        } // for s in sector's edges
		n++;
	}
    ++renderedsectors[now.sectorno];
	}  // render any other queued sectors
	return (0);
}
*/

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