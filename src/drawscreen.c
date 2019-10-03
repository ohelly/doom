/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawscreen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 18:33:12 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/03 20:26:18 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_scaler	scaler_init(t_ab_i wy, int cya, int u0, int u1)
{
	t_scaler t;

	t.result = u0 + (cya - 1 - wy.a) * (u1 - u0) / (wy.b - wy.a);
	t.bop = ((u1 < u0) ^ ((wy.b < wy.a)) ? -1 : 1);
	t.fd = abs(u1 - u0);
	t.ca = abs(wy.b - wy.a);
	t.cache = ((cya - 1 - wy.a) * abs(u1 - u0) % abs(wy.b - wy.a));
	return (t);
}

static int scaler_next(t_scaler* i)
{
    for (i->cache += i->fd; i->cache >= i->ca; i->cache -= i->ca)
		i->result += i->bop;
    return (i->result);
}

void		vline(int x, int y1,int y2, int top, int middle, int bottom, t_sdl *sdl)
{
	int		y;

    y1 = clamp(y1, 0, HEIGHT - 1);
    y2 = clamp(y2, 0, HEIGHT - 1);
    if (y2 == y1)
        sdl->pix[y1 * WIDTH + x] = middle;
    else if (y2 > y1)
    {
        sdl->pix[y1 * WIDTH + x] = top;
		y = y1 + 1;
        while (y < y2)
		{
			sdl->pix[y * WIDTH + x] = middle;
			y++;
		}
        sdl->pix[y2 * WIDTH + x] = bottom;
    }
}

void	vline2(int x, t_ab wy, t_scaler ty, t_doom *doom)
{
	int		*pix;
	int		txty;
	int		y;
	int		y1 = wy.a;
	int		y2 = wy.b;
	int		t;

	pix = doom->sdl->pix;
    y1 = clamp(y1, 0, HEIGHT - 1);
    y2 = clamp(y2, 0, HEIGHT - 1);
    pix += y1 * WIDTH + x;
	y = y1;
	t = doom->sector[doom->now.sector].txtw;
    while (y <= y2)
    {
        txty = scaler_next(&ty);
		*pix = doom->txt->img[t].data[txty % doom->txt->img[t].h * doom->txt->img[t].w + doom->cood.txtx % doom->txt->img[t].w];
        pix += WIDTH;
		y++;
    }
}

int			checkneighbor(t_doom *doom, t_cood *cood, int x, t_ab cy)
{
	t_ab_i	wny;
	t_ab_i	cny;
	t_scaler t;
	t_ab	rny;

	if (cood->neighbor >= 0)
	{
		wny.a = (x - cood->w1.x) * (cood->n2y.a - cood->n1y.a) / (cood->w2.x - cood->w1.x) + cood->n1y.a;
		cny.a = clamp(wny.a, doom->ytop[x], doom->ybot[x]);
		wny.b = (x - cood->w1.x) * (cood->n2y.b - cood->n1y.b) / (cood->w2.x - cood->w1.x) + cood->n1y.b;
		cny.b = clamp(wny.b, doom->ytop[x], doom->ybot[x]);
		rny.a = cy.a;
		rny.b = cny.a - 1;
		vline2(x, rny, scaler_init(cood->wy, cy.a, 0, doom->txt->img[doom->sector[doom->now.sector].txtw].w * 8), doom);
		doom->ytop[x] = clamp(max(cy.a, cny.a), doom->ytop[x], HEIGHT - 1);	
		rny.a = cny.b;
		rny.b = cy.b - 1;
	    vline2(x, rny, scaler_init(cood->wy, cny.b + 1, 0,  doom->txt->img[doom->sector[doom->now.sector].txtw].w * 8), doom);
	    doom->ybot[x] = clamp(min(cy.b, cny.b), 0, doom->ybot[x]);
	}
	else
	{
		vline2(x, cy, scaler_init(cood->wy, cy.a, 0, doom->txt->img[doom->sector[doom->now.sector].txtw].w * 8), doom);
	}
	return (0);
}

/*
#define CeilingFloorScreenCoordinatesToMapCoordinates(mapY, screenX,screenY, X,Z) \
    do { Z = (mapY) * HEIGHT * VFOV / ((HEIGHT / 2 - (screenY)) - doom->player.yaw * HEIGHT * VFOV); \
    X = (Z) * (WIDTH / 2 - (screenX)) / (WIDTH * HFOV); \
    RelativeMapCoordinatesToAbsoluteOnes(X,Z); } while(0)
                //
 #define RelativeMapCoordinatesToAbsoluteOnes(X,Z) \
    do { float rtx = (Z) * doom->player.anglecos + (X) * doom->player.anglesin; \
    float rtz = (Z) * doom->player.anglesin - (X) * doom->player.anglecos; \
    X = rtx + doom->player.where.x; Z = rtz + doom->player.where.y; \
	} while(0)
*/

void	RelativeMapCoordinatesToAbsoluteOnes(float *X, float *Z, t_player player) \
{
    do { float rtx = (*Z) * player.anglecos + (*X) * player.anglesin; \
    float rtz = (*Z) * player.anglesin - (*X) * player.anglecos; \
    *X = rtx + player.where.x; *Z = rtz + player.where.y; \
	} while(0);
}

void	CeilingFloorScreenCoordinatesToMapCoordinates(float mapY, int screenX, int screenY, float *X, float *Z, t_player player)
{
	do {
    *Z = (mapY) * HEIGHT * VFOV / ((HEIGHT / 2 - (screenY)) - player.yaw * HEIGHT * VFOV); \
    *X = (*Z) * (WIDTH / 2 - (screenX)) / (WIDTH * HFOV); \
    RelativeMapCoordinatesToAbsoluteOnes(X, Z, player);
	} while (0);
}
                //


/*
void		RelativeMapCoordinatesToAbsoluteOnes(float *X, float *Z, t_player player)
{
	do {
	float rtx = *Z * player.anglecos + *X * player.anglesin;
    float rtz = *Z * player.anglesin - *X * player.anglecos;
    *X = rtx + player.where.x;
	*Z = rtz + player.where.y;
	} while (0);
}

void		CeilingFloorScreenCoordinatesToMapCoordinates(float mapy, int screenx, int screeny, float *X, float *Z, t_player player)
{
	do {
	*Z = mapy * HEIGHT * VFOV / ((HEIGHT / 2) - screeny) - player.yaw * HEIGHT * VFOV;
	*X = *Z * (WIDTH / 2 - screenx) / (WIDTH * HFOV);
	RelativeMapCoordinatesToAbsoluteOnes(X,Z, player);
	} while (0);
}
*/

int			beginrender(t_doom *doom, t_cood *cood, t_player player, int n)
{
	t_ab	cy;
	t_ab_i	wy;
	int		beginx;
	int		endx;
	int		x;
	int		y;
	float	hei;
	float 	mapx, mapz;
	int		t;
	t_img 	set;

	beginx = max(cood->w1.x, doom->now.sx);
	endx = min(cood->w2.x, doom->now.ex);
	cood->beginx = beginx;
	cood->endx = endx;
	x = beginx;
	while (x <= endx)
	{
		cood->txtx = (cood->u0 * ((cood->w2.x - x) * cood->t2.z) + cood->u1 * ((x - cood->w1.x) * cood->t1.z)) / ((cood->w2.x - x) * cood->t2.z + (x - cood->w1.x) * cood->t1.z);
		wy.a = (x - cood->w1.x) * (cood->w2y.a - cood->w1y.a) / (cood->w2.x - cood->w1.x) + cood->w1y.a;
		cy.a = clamp(wy.a, doom->ytop[x], doom->ybot[x]);
		wy.b = (x - cood->w1.x) * (cood->w2y.b - cood->w1y.b) / (cood->w2.x - cood->w1.x) + cood->w1y.b;
		cy.b = clamp(wy.b, doom->ytop[x], doom->ybot[x]);
		doom->ybot[x] = clamp(doom->ybot[x], 0, HEIGHT - 1);
		t = cood->s->txtw;
		y = doom->ytop[x];
		while (y <= doom->ybot[x])
		{
			if (y >= cy.a - 1 && y <= cy.b)
			{
				y = cy.b;
				y++;
				continue ;
			}
			hei = y < cy.a ? cood->s->ceil - player.where.z : cood->s->floor - player.where.z;
			CeilingFloorScreenCoordinatesToMapCoordinates(hei, x,y, &mapx, &mapz, player);
            int txtx = (mapx * 32);
			int txtz = (mapz * 32);
			set = y < cy.a ? doom->txt->img[cood->s->txtc] : doom->txt->img[cood->s->txtf];
			int pel = set.data[(txtz % set.h) * set.w + (txtx % set.w)];
        	doom->sdl->pix[y * WIDTH + x] = pel;
			y++;
		}
		cood->wy = wy;
		//vline(x, doom->ytop[x], cy.a - 1, 0x22222, 0xFFFFFF, 0x222222, doom->sdl); //потолок
		//vline(x, cy.b + 1, doom->ybot[x], 0, 0xFFFFFF, 0, doom->sdl); //пол
		checkneighbor(doom, cood, x, cy);
		x++;
	}
	return (0);
}

int			findnyceilandnyfloor(t_doom *doom, t_cood *cood, t_player player, int n)
{
	t_f ny;

	ny.ceil  = doom->sector[cood->neighbor].ceil  - player.where.z; 
	ny.floor = doom->sector[cood->neighbor].floor - player.where.z;
	cood->n1y.a = HEIGHT / 2 - (int)(yaw(ny.ceil , cood->t1.z, player) * cood->scale1.y);
	cood->n1y.b = HEIGHT / 2 - (int)(yaw(ny.floor, cood->t1.z, player) * cood->scale1.y);
	cood->n2y.a = HEIGHT / 2 - (int)(yaw(ny.ceil , cood->t2.z, player) * cood->scale2.y);
	cood->n2y.b = HEIGHT / 2 - (int)(yaw(ny.floor, cood->t2.z, player) * cood->scale2.y);
	return (0);
}

int			findyceilandyfloor(t_doom *doom, t_cood *cood, t_player player, int n)
{
	t_f		y;
	y.ceil = cood->s->ceil - player.where.z;
	y.floor = cood->s->floor - player.where.z;
	cood->neighbor = doom->sector[doom->now.sector].neighbors[n];
	if (cood->neighbor >= 0)
		findnyceilandnyfloor(doom, cood, player, n);
	cood->w1y.a = HEIGHT / 2 - (int)(yaw(y.ceil , cood->t1.z, player) * cood->scale1.y);
	cood->w1y.b = HEIGHT / 2 - (int)(yaw(y.floor, cood->t1.z, player) * cood->scale1.y);
	cood->w2y.a = HEIGHT / 2 - (int)(yaw(y.ceil , cood->t2.z, player) * cood->scale2.y);
	cood->w2y.b = HEIGHT / 2 - (int)(yaw(y.floor, cood->t2.z, player) * cood->scale2.y);
	beginrender(doom, cood, player, n);
	return (0);
}

int			findxscale(t_doom *doom, t_cood *cood, t_player player, int n)
{
	
	cood->scale1.x = (HFOV * WIDTH) / cood->t1.z;
	cood->scale1.y = (VFOV * HEIGHT) / cood->t1.z;
	cood->scale2.x = (HFOV * WIDTH) / cood->t2.z;
	cood->scale2.y = (VFOV * HEIGHT) / cood->t2.z;
	cood->w1.x = WIDTH / 2 - (int)(cood->t1.x * cood->scale1.x);
	cood->w2.x = WIDTH / 2 - (int)(cood->t2.x * cood->scale2.x);
	if(cood->w1.x >= cood->w2.x || cood->w2.x < doom->now.sx || cood->w1.x > doom->now.ex)
		return (0);
	findyceilandyfloor(doom, cood, player, n);
	return (1);
}

void		difference(t_xy v, t_xyz p, t_xyz *res)
{
	res->x = v.x - p.x;
	res->y = v.y - p.y;
}

void		rotation(t_xyz v, float psin, float pcos, t_xyz *t)
{
	t->x = v.x * psin - v.y * pcos;
	t->z = v.x * pcos + v.y * psin;
}

t_xy		findintersect(t_xyz *t1, t_xyz *t2, int sign)
{
	t_xy	i;
	
	i.x = vxs(vxs(t1->x, t1->z, t2->x, t2->z), t1->x - t2->x, vxs(NEARSIDE * sign, NEARZ, FARSIDE * sign, FARZ), NEARSIDE * sign - FARSIDE * sign)
	/ vxs(t1->x - t2->x, t1->z - t2->z, NEARSIDE * sign - FARSIDE * sign, NEARZ - FARZ);
	i.y = vxs(vxs(t1->x, t1->z, t2->x, t2->z), t1->z - t2->z, vxs(NEARSIDE * sign, NEARZ, FARSIDE * sign, FARZ), NEARZ - FARZ)
	/ vxs(t1->x - t2->x, t1->z - t2->z, NEARSIDE * sign - FARSIDE * sign, NEARZ - FARZ);
	return (i);
}

void		iflower(t_xyz *t, t_xy i1, t_xy i2)
{
	if (i1.y > 0)
	{
		t->x = i1.x;
		t->z = i1.y;
	}
	else
	{
		t->x = i2.x;
		t->z = i2.y;
	}
}

int			intersect(t_xyz *t1, t_xyz *t2, t_cood *cood)
{
	t_xy	i1;
	t_xy	i2;
	float		nearz = 1e-4f, farz = 5, nearside = 1e-5f, farside = 20.f;
	
	i1 = findintersect(t1, t2, -1);
	i2 = findintersect(t1, t2, 1);//findintersect(t1, t2, 1);
	cood->org1.x = t1->x;
	cood->org1.y = t1->z;
	cood->org2.x = t2->x;
	cood->org2.y = t2->z;
	if (t1->z < NEARZ)
		iflower(t1, i1, i2);
	if (t2->z < NEARZ)
		iflower(t2, i1, i2);
	
	return (0);
}

int			calc_points(t_doom *doom, t_player player, t_cood *cood, int n)
{
	int		t;

	difference(cood->s->vert[n], doom->player.where, &cood->v1); //v1 = vert - player
	difference(cood->s->vert[n + 1], doom->player.where, &cood->v2);
	rotation(cood->v1, doom->player.anglesin, doom->player.anglecos, &cood->t1);//t1 = v1.x * sin - v1.y * cos ...
	rotation(cood->v2, doom->player.anglesin, doom->player.anglecos, &cood->t2);
	if (cood->t1.z <= 0 && cood->t2.z <= 0)
		return (0);
	t = doom->now.sector;
	cood->u0 = 0;
	cood->u1 = doom->txt->img[t].w * 4; // если приравнять размеру текстуры, то растянет по всей стене
	if (cood->t1.z <= 0 || cood->t2.z <= 0)
	{
		intersect(&cood->t1, &cood->t2, cood);
		if (fabs(cood->t2.x - cood->t1.x) > fabs(cood->t2.z - cood->t1.z))
		{
			cood->u0 = (cood->t1.x - cood->org1.x) * cood->u1 / (cood->org2.x - cood->org1.x);
			cood->u1 = (cood->t2.x - cood->org1.x) * cood->u1 / (cood->org2.x - cood->org1.x);
		}
		else
		{
			cood->u0 = (cood->t1.z - cood->org1.y) * cood->u1 / (cood->org2.y - cood->org1.y);
			cood->u1 = (cood->t2.z - cood->org1.y) * cood->u1 / (cood->org2.y - cood->org1.y);
		}
	}
	if (!(findxscale(doom, cood, player, n)))
		return (0);
	return (1);
}

int			renew(t_item *head, t_doom *doom, int *rensects)
{
	int		x;

	ft_memset(doom->ybot, HEIGHT - 1, WIDTH * 4);
	ft_memset(doom->ytop, 0, WIDTH * 4);
	ft_memset(rensects, 0, doom->numsectors);
	x = 0;
	while (x < doom->numsectors)
	{
		doom->item[x].sector = 0;
		x++;
	}
	head->sx = 0;
	head->ex = WIDTH - 1;
	head->sector = doom->player.sector;
	return (0);
}

int			calcsector(t_doom *doom, t_cood *cood, t_player player)
{
	int		n;

	n = 0;
	while (n < cood->s->npoints)
	{
		if (!(calc_points(doom, doom->player, cood, n)))
		{
			n++;
			continue ;
		}
		n++;
		doom->item[doom->now.sector].ytop = doom->ytop;
		doom->item[doom->now.sector].ybot = doom->ybot;
		if(cood->neighbor >= 0 && cood->endx >= cood->beginx && (doom->head + 32 + 1 - doom->tail) % 32)
        {
			doom->head->sector = cood->neighbor;
			doom->head->sx = cood->beginx;
			doom->head->ex = cood->endx;
        	if(++doom->head == doom->queue + 32)
				doom->head = doom->queue;
        }
	}
	return (0);
}

int			assignvalue(t_item *item, t_item now, int *rensects)
{
	item[now.sector].sx = now.sx;
	item[now.sector].ex = now.ex;
	item[now.sector].sector = rensects[now.sector];
	return (0);
}

int			drawwalls(t_doom *doom, t_player player)
{
	int		rensects[doom->numsectors];

	doom->head = doom->queue;
	doom->tail = doom->queue;
	renew(doom->head, doom, rensects);
	if (++doom->head == doom->queue + 32)
		doom->head = doom->queue;
	while (doom->head != doom->tail)
	{
		doom->now = *doom->tail;
		if (++doom->tail == doom->queue + 32)
			doom->tail = doom->queue;
		if (rensects[doom->now.sector] == 1)
			continue ;
		++rensects[doom->now.sector];
		assignvalue(&doom->item[doom->now.sector], doom->now, rensects);
		doom->cood.s = &doom->sector[doom->now.sector];
		calcsector(doom, &doom->cood, doom->player);
		++rensects[doom->now.sector];
	}
	return (0);
}

int			drawscreen(t_doom *doom)
{	
	drawwalls(doom, doom->player);
	drawsprites(doom, doom->obj, doom->player);
	return (0);
}
