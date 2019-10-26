/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawscreen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 18:33:12 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/26 04:32:32 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_scaler	scaler_init(t_ab_i wy, int cya, int u0, int u1)
{
	t_scaler t;

	if ((wy.b - wy.a) == 0)
		wy.b -= 1;
	t.result = (u0 + (cya - 1 - wy.a) * (u1 - u0) / (wy.b - wy.a));
	t.bop = ((u1 < u0) ^ ((wy.b < wy.a)) ? -1 : 1);
	t.fd = abs(u1 - u0);
	t.ca = abs(wy.b - wy.a);
	t.cache = (cya - 1 - wy.a) * abs(u1 - u0) % abs(wy.b - wy.a);
	return (t);
}

int		scaler_next(t_scaler* i)
{
    for (i->cache += i->fd; i->cache >= i->ca; i->cache -= i->ca)
		i->result += i->bop;
    return (i->result);
}

void	RelativeMapCoordinatesToAbsoluteOnes(float *X, float *Z, t_player player) \
{
	float rtx = (*Z) * player.pcos + (*X) * player.psin; \
    float rtz = (*Z) * player.psin - (*X) * player.pcos; \
    *X = rtx + player.where.x; *Z = rtz + player.where.y; \
}

void	CeilingFloorScreenCoordinatesToMapCoordinates(float mapY, int screenX, int screenY, float *X, float *Z, t_player player)
{
    *Z = (mapY) * HEIGHT * VFOV / ((HEIGHT / 2 - (screenY)) - player.yaw * HEIGHT * VFOV); \
    *X = (*Z) * (WIDTH / 2 - (screenX)) / (WIDTH * HFOV); \
    RelativeMapCoordinatesToAbsoluteOnes(X, Z, player);
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

void	vline2(int x, t_ab_i wy, t_scaler ty, t_doom *doom)
{
	int		*pix;
	int		txty;
	int		y;
	int		y1 = wy.a;
	int		y2 = wy.b;
	int		t;
	int		color;
	static int		prev_color;
	static int		prev_light;
	t_sectors	*s;
	t_img		*set;

	pix = doom->sdl->pix;
    y1 = clamp(y1, 0, HEIGHT - 1);
    y2 = clamp(y2, 0, HEIGHT - 1);
    pix += y1 * WIDTH + x;
	y = y1;
	s = &doom->sectors[doom->now.sector];
	set = &doom->img[doom->walls[s->txtw[doom->cood.n]].image];
    while (y < y2)
    {
		if (doom->cood.neighbor == -2)
		{
			doom->visible[y][x] = 1;
			y++;
			continue ;
		}
        txty = scaler_next(&ty);
		color = set->data[txty % set->h * set->w + doom->cood.txtx % set->w];
		if (color != prev_color)
		{
			prev_color = color;
			prev_light = rgb_multiply(color, s->light);
		}
		*pix = prev_light;
        pix += WIDTH;
		y++;
    }
}

void	vline3(int x, t_ab_i wy, t_scaler ty, t_doom *doom)
{
	int		*pix;
	int		txty;
	int		y;
	int		y1 = wy.a;
	int		y2 = wy.b;
	int		t;
	int		color;
	static int		prev_color;
	static int		prev_light;
	t_img	set;

	pix = doom->sdl->pix;
    y1 = clamp(y1, 0, HEIGHT - 1);
    y2 = clamp(y2, 0, HEIGHT - 1);
    pix += y1 * WIDTH + x;
	y = y1;
	if (doom->isshoot)
		set = doom->img[doom->shot_pics[doom->cood.num].images[0][0]];
	else
		set = doom->img[doom->pics[doom->cood.num].images[doom->pics[doom->cood.num].states_frame][doom->pics[doom->cood.num].anim_frame]];
    while (y <= y2)
    {
        txty = scaler_next(&ty);
		color = set.data[txty % set.h * set.w + doom->cood.ptxtx % set.w];
		if (color)
		{
			if (x >= WIDTH / 2 - doom->weapon[doom->player.weapon].scatterx &&
				x <= WIDTH / 2 + doom->weapon[doom->player.weapon].scatterx &&
				y >= HEIGHT / 2 - doom->weapon[doom->player.weapon].scattery &&
				y <= HEIGHT / 2 + doom->weapon[doom->player.weapon].scattery)
				doom->pic_interaction[doom->cood.num] = 1;
		
			if (color != prev_color)
			{
				prev_color = color;
				prev_light = rgb_multiply(color, doom->sectors[doom->now.sector].light);
			}
			*pix = prev_light;
		}
        pix += WIDTH;
		y++;
    }
}

int			renew(t_item *head, t_doom *doom, int *rensects)
{
	int		x;
	int		y;
	int		i;
	x = 0;
	while (x < WIDTH)
	{
		doom->ybot[x] = HEIGHT - 1;
		doom->ytop[x] = 0;
		x++;
	}
	i = 0;
	while (i < doom->num.pics)
	{
		doom->pic_interaction[i] = 0;
		i++;
	}
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			doom->visible[y][x] = 0;
			x++;
		}
		y++;
	}
	x = 0;
	while (x < doom->num.sectors)
	{
		doom->lookwall[x] = -1;
		doom->item[x].sector = 0;
		rensects[x] = 0;
		x++;
	}
	head->sx = 0;
	head->ex = WIDTH - 1;
	head->sector = doom->player.sector;
	return (0);
}

int			assign_value(t_item *item, t_item now, int *rensects)
{
	item[now.sector].sx = now.sx;
	item[now.sector].ex = now.ex;
	item[now.sector].sector = rensects[now.sector];
	return (0);
}

int			find_t_points(t_xy *v, t_player player, t_cood *cood)
{
	cood->v1.x = v[cood->n].x - player.where.x;
	cood->v1.y = v[cood->n].y - player.where.y;
	cood->v2.x = v[cood->n + 1].x - player.where.x;
	cood->v2.y = v[cood->n + 1].y - player.where.y;
	cood->t1.x = cood->v1.x * player.psin - cood->v1.y * player.pcos;
	cood->t1.z = cood->v1.x * player.pcos + cood->v1.y * player.psin;
	cood->t2.x = cood->v2.x * player.psin - cood->v2.y * player.pcos;
	cood->t2.z = cood->v2.x * player.pcos + cood->v2.y * player.psin;
	return (0);
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
	i2 = findintersect(t1, t2, 1);
	cood->org1.x = t1->x;
	cood->org1.y = t1->z;
	cood->org2.x = t2->x;
	cood->org2.y = t2->z;
	if (t1->z < NEARZ)
		iflower(t1, i1, i2);
	if (t2->z < NEARZ)
		iflower(t2, i1, i2);
		
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
	return (0);
}

int			render_ceil_floor(t_doom *doom, t_sectors *s, t_cood *cood, t_player player)
{
	float 	mapx;
	float	mapz;
	int 	txtx;
	int 	txtz;
	int		pel;
	static int	prev_light;
	static int	prev_color;
	float	hei;
	t_img	set;

	hei = cood->y < cood->cy.a ? cood->yceil : cood->yfloor;
	if (s->sky == 1 && hei == cood->yceil)
	{
		doom->visible[cood->y][cood->x] = 1;
		return (0);
	}
	CeilingFloorScreenCoordinatesToMapCoordinates(hei, cood->x, cood->y, &mapx, &mapz, player);
    txtx = (mapx * 8);
	txtz = (mapz * 8);
	set = cood->y < cood->cy.a - 1 ? doom->img[doom->ceils[s->txtc].image] : doom->img[doom->floors[s->txtf].image];
	pel = set.data[(txtz % set.h) * set.w + (txtx % set.w)];
	if (pel != prev_color)
	{
		prev_light = rgb_multiply(pel, s->light);
		prev_color = pel;
	}
	doom->sdl->pix[cood->y * WIDTH + cood->x] = prev_light;
	if (!set.data[(txtz % set.h) * set.w + (txtx % set.w)])
	{
		doom->visible[cood->y][cood->x] = 1;
		return (0);
	}
	return (1);
}

int			draw_ceil_floor(t_doom *doom, t_sectors *s, t_cood *cood, t_player player)
{
	float	hei;
	int		ty = 0;
	int		tx = 0;
	int		y;

	y = doom->ytop[cood->x];
	while (y <= doom->ybot[cood->x])
	{
		if (y >= cood->cy.a - 1 && y <= cood->cy.b - 1)
		{
			y = cood->cy.b - 1;
			y++;
			continue ;
		}
		cood->y = y;
		if (!(render_ceil_floor(doom, s, cood, player)))
		{
			y++;
			continue ;
		}
		y++;
	}
	return (0);
}

int			render_walls2(t_doom *doom, t_sectors *s, t_cood *cood, t_player player)
{
	t_ab_i	scaler;

	if (cood->neighbor >= 0)
	{
		cood->ny.a = (cood->x - cood->w1x) * (cood->n2y.a - cood->n1y.a) / (cood->w2x - cood->w1x) + cood->n1y.a;
		cood->cny.a = clamp(cood->ny.a, doom->ytop[cood->x], doom->ybot[cood->x]);
		cood->ny.b = (cood->x - cood->w1x) * (cood->n2y.b - cood->n1y.b) / (cood->w2x - cood->w1x) + cood->n1y.b;
		cood->cny.b = clamp(cood->ny.b, doom->ytop[cood->x], doom->ybot[cood->x]);
		scaler.a = cood->cy.a;
		scaler.b = cood->cny.a - 1;
		vline2(cood->x, scaler, scaler_init(cood->wy, cood->cy.a, 0, doom->img[doom->walls[s->txtw[cood->n]].image].w), doom);
		doom->ytop[cood->x] = clamp(max(cood->cy.a, cood->cny.a - 1), doom->ytop[cood->x], HEIGHT - 1);	
		scaler.a = cood->cny.b;
		scaler.b = cood->cy.b - 1;
	    vline2(cood->x, scaler, scaler_init(cood->wy, cood->cny.b, 0, doom->img[doom->walls[s->txtw[cood->n]].image].w), doom);
	    doom->ybot[cood->x] = clamp(min(cood->cy.b, cood->cny.b), 0, doom->ybot[cood->x]);
	}
	else
		vline2(cood->x, cood->cy, scaler_init(cood->wy, cood->cy.a, 0, doom->img[doom->walls[s->txtw[cood->n]].image].w), doom);
	return (0);
}

int			render_pics(t_doom *doom, t_cood *cood, int x) 
{
	int		i;
	t_img	img;

	i = 0;
	while (i < cood->piccount)
	{
		img = pic_get_image(doom, &doom->pics[cood->num]);
		if (x >= cood->pw1x[i] && x <= cood->pw2x[i])
		{
			cood->ptxtx = (cood->pu0[i] * ((cood->pw2x[i] - x) * cood->pt2[i].z) + cood->pu1[i] * ((x - cood->pw1x[i]) * cood->pt1[i].z)) / ((cood->pw2x[i] - x) * cood->pt2[i].z + (x - cood->pw1x[i]) * cood->pt1[i].z);
			cood->pwy[i].a = (x - cood->pw1x[i]) * (cood->pw2y[i].a - cood->pw1y[i].a) / (cood->pw2x[i] - cood->pw1x[i]) + cood->pw1y[i].a;
			cood->pcy[i].a = clamp(cood->pwy[i].a, doom->ytop[x], doom->ybot[x]);
			cood->pwy[i].b = (x - cood->pw1x[i]) * (cood->pw2y[i].b - cood->pw1y[i].b) / (cood->pw2x[i] - cood->pw1x[i]) + cood->pw1y[i].b;
			cood->pcy[i].b = clamp(cood->pwy[i].b, doom->ytop[x], doom->ybot[x]);
			cood->num = cood->picnum[i];
			vline3(x, cood->pcy[i], scaler_init(cood->pwy[i], cood->pcy[i].a, 0, img.w), doom);		
		}
		i++;
	}
	return (0);
}

int			render_walls(t_doom *doom, t_sectors *s, t_cood *cood, t_player player)
{
	int		x;
	int		i;

	cood->beginx = max(cood->w1x, doom->now.sx);
	cood->endx = min(cood->w2x, doom->now.ex);
	x = cood->beginx;
	while (x <= cood->endx)
	{
		if (x == WIDTH / 2)
			doom->lookwall[doom->now.sector] = cood->n;
		cood->x = x;
		cood->txtx = (cood->u0 * ((cood->w2x - x) * cood->t2.z) + cood->u1 * ((x - cood->w1x) * cood->t1.z)) / ((cood->w2x - x) * cood->t2.z + (x - cood->w1x) * cood->t1.z);
		cood->wy.a = (x - cood->w1x) * (cood->w2y.a - cood->w1y.a) / (cood->w2x - cood->w1x) + cood->w1y.a;
		cood->cy.a = clamp(cood->wy.a, doom->ytop[x], doom->ybot[x]);
		cood->wy.b = (x - cood->w1x) * (cood->w2y.b - cood->w1y.b) / (cood->w2x - cood->w1x) + cood->w1y.b;
		cood->cy.b = clamp(cood->wy.b, doom->ytop[x], doom->ybot[x]);
		draw_ceil_floor(doom, s, cood, player);
		render_walls2(doom, s, cood, player);
		render_pics(doom, cood, x);
		x++;
	}
	
	return (0);
}

int			find_scales(t_doom *doom, t_sectors *s, t_cood *cood, t_player player)
{
	cood->scale1.x = (HFOV * WIDTH) / cood->t1.z;
	cood->scale1.y = (VFOV * HEIGHT) / cood->t1.z;
	cood->scale2.x = (HFOV * WIDTH) / cood->t2.z;
	cood->scale2.y = (VFOV * HEIGHT) / cood->t2.z;

	cood->w1x = WIDTH / 2 - (int)(cood->t1.x * cood->scale1.x);
	cood->w2x = WIDTH / 2 - (int)(cood->t2.x * cood->scale2.x);
	
	if (cood->w1x == cood->w2x)// || cood->w1x < -10000 || cood->w2x < doom->now.sx || cood->w1x > doom->now.ex)
		return (0);
	//printf("w1x - %d, w2x - %d\n", cood->w1x, cood->w2x);
	return (1);
}

int			find_yceil_yfloor(t_doom *doom, t_sectors *s, t_cood *cood, t_player player)
{
	cood->yceil = s->ceil - player.where.z;
	cood->yfloor = s->floor - player.where.z;
	cood->neighbor = s->neighbors[cood->n];
	if (cood->neighbor >= 0)
	{
		cood->nyceil  = doom->sectors[cood->neighbor].ceil - player.where.z; 
		cood->nyfloor = doom->sectors[cood->neighbor].floor - player.where.z;
		cood->n1y.a = HEIGHT / 2 - (int)(yaw(cood->nyceil , cood->t1.z, player) * cood->scale1.y);
		cood->n1y.b = HEIGHT / 2 - (int)(yaw(cood->nyfloor, cood->t1.z, player) * cood->scale1.y);
		cood->n2y.a = HEIGHT / 2 - (int)(yaw(cood->nyceil , cood->t2.z, player) * cood->scale2.y);
		cood->n2y.b = HEIGHT / 2 - (int)(yaw(cood->nyfloor, cood->t2.z, player) * cood->scale2.y);
	}
	cood->w1y.a = HEIGHT / 2 - (int)(yaw(cood->yceil , cood->t1.z, player) * cood->scale1.y);
	cood->w1y.b = HEIGHT / 2 - (int)(yaw(cood->yfloor, cood->t1.z, player) * cood->scale1.y);
	cood->w2y.a = HEIGHT / 2 - (int)(yaw(cood->yceil , cood->t2.z, player) * cood->scale2.y);
	cood->w2y.b = HEIGHT / 2 - (int)(yaw(cood->yfloor, cood->t2.z, player) * cood->scale2.y);
	return (0);
}

int			calc_pics(t_doom *doom, t_pics *pic, t_cood *cood, t_player player)
{
	int		i;
	int		count;
	t_xy	i1;
	t_xy	i2;
	float		nearz = 1e-4f, farz = 5, nearside = 1e-5f, farside = 20.f;

	i = 0;
	count = 0;
	/*
	while (i < cood->piccount)
	{
		cood->pu0[i] = 0;
		cood->pu1[i] = 0;
		cood->pyceil[i] = 0;
		cood->pyfloor[i] = 0;
		cood->pv1[i] = (t_xyz){0, 0, 0};
		cood->pv2[i] = (t_xyz){0, 0, 0};
		cood->pt1[i] = (t_xyz){0, 0, 0};
		cood->pt2[i] = (t_xyz){0, 0, 0};
		cood->porg1[i] = (t_xy){0, 0};
		cood->porg2[i] = (t_xy){0, 0};
		cood->pscale1[i] = (t_xy){0, 0};
		cood->pscale2[i] = (t_xy){0, 0};
		cood->pw1x[i] = 0;
		cood->pw2x[i] = 0;
		cood->pwy[i] = (t_ab_i){0, 0}; 
		cood->pwx[i] = (t_ab_i){0, 0}; //current point
		cood->pcy[i] = (t_ab_i){0, 0};
		cood->pw1y[i] = (t_ab_i){0, 0};
		cood->pw2y[i] = (t_ab_i){0, 0};
		cood->picnum[i] = 0;
		i++;
	}
	*/
	while (i < doom->num.pics)
	{
		if (pic[i].wall == cood->n && pic[i].sector == doom->now.sector)
		{
			//printf("px - %f, py - %f\n", pic[i].p.x, pic[i].p.y);
			//printf("Px - %f, Py - %f\n", pic[i].p.x, pic[i].p.y);	pic[i].anim_frame++;
			if (doom->a == 1)
			{
				pic[i].anim_frame++;
				if (pic[i].anim_frame >= pic[i].anim_count[pic[i].states_frame] ||
					pic[i].images[pic[i].states_frame][pic[i].anim_frame] == -1)
					pic[i].anim_frame = 0;
			}
			//printf("satte - %d, anim - %d\n", pic[i].states_frame, pic[i].anim_frame);
			cood->picnum[count] = i;
			cood->pv1[count].x = pic[i].p1.x - player.where.x;
			cood->pv1[count].y = pic[i].p1.y - player.where.y;
			cood->pv2[count].x = pic[i].p2.x - player.where.x;
			cood->pv2[count].y = pic[i].p2.y - player.where.y;

			cood->pt1[count].x = cood->pv1[count].x * player.psin - cood->pv1[count].y * player.pcos;
			cood->pt1[count].z = cood->pv1[count].x * player.pcos + cood->pv1[count].y * player.psin;
			cood->pt2[count].x = cood->pv2[count].x * player.psin - cood->pv2[count].y * player.pcos;
			cood->pt2[count].z = cood->pv2[count].x * player.pcos + cood->pv2[count].y * player.psin;
			if (cood->pt1[count].z <= 0 && cood->pt2[count].z <= 0)
			{
				i++;
				continue ;
			}
			cood->pu0[count] = 0;
			cood->pu1[count] = doom->img[pic[i].images[pic[i].states_frame][pic[i].anim_frame]].w;
			if (cood->pt1[count].z <= 0 || cood->pt2[count].z <= 0)
			{
				i1 = findintersect(&cood->pt1[count], &cood->pt2[count], -1);
				i2 = findintersect(&cood->pt1[count], &cood->pt2[count], 1);
				cood->porg1[count].x = cood->pt1[count].x;
				cood->porg1[count].y = cood->pt1[count].z;
				cood->porg2[count].x = cood->pt2[count].x;
				cood->porg2[count].y = cood->pt2[count].z;
				if (cood->pt1[count].z < NEARZ)
					iflower(&cood->pt1[count], i1, i2);
				if (cood->pt2[count].z < NEARZ)
					iflower(&cood->pt2[count], i1, i2);
				if (fabs(cood->pt2[count].x - cood->pt1[count].x) > fabs(cood->pt2[count].z - cood->pt1[count].z))
				{
					cood->pu0[count] = (cood->pt1[count].x - cood->porg1[count].x) * cood->pu1[count] / (cood->porg2[count].x - cood->porg1[count].x);
					cood->pu1[count] = (cood->pt2[count].x - cood->porg1[count].x) * cood->pu1[count] / (cood->porg2[count].x - cood->porg1[count].x);
				}
				else
				{
					cood->pu0[count] = (cood->pt1[count].z - cood->porg1[count].y) * cood->pu1[count] / (cood->porg2[count].y - cood->porg1[count].y);
					cood->pu1[count] = (cood->pt2[count].z - cood->porg1[count].y) * cood->pu1[count] / (cood->porg2[count].y - cood->porg1[count].y);
				}
			}
			cood->pscale1[count].x = (HFOV * WIDTH) / cood->pt1[count].z;
			cood->pscale1[count].y = (VFOV * HEIGHT) / cood->pt1[count].z;
			cood->pscale2[count].x = (HFOV * WIDTH) / cood->pt2[count].z;
			cood->pscale2[count].y = (VFOV * HEIGHT) / cood->pt2[count].z;
			cood->pw1x[count] = WIDTH / 2 - (int)(cood->pt1[count].x * cood->pscale1[count].x);
			cood->pw2x[count] = WIDTH / 2 - (int)(cood->pt2[count].x * cood->pscale2[count].x);
			//printf("w1x - %d, w2x - %d\n", cood->pw1x[count], cood->pw2x[count]);
			if (cood->pw1x[count] == cood->pw2x[count])// || cood->pw2x[count] < doom->now.sx || cood->pw1x[count] > doom->now.ex)
			{
				i++;
				continue ;
			}
			cood->pyceil[count] = pic[i].p.z + doom->sectors[doom->now.sector].floor + (float)(doom->img[pic[i].images[pic[i].states_frame][pic[i].anim_frame]].h) / 9.f - player.where.z;
			cood->pyfloor[count] = pic[i].p.z + doom->sectors[doom->now.sector].floor - player.where.z;
			cood->pw1y[count].a = HEIGHT / 2 - (int)(yaw(cood->pyceil[count] , cood->pt1[count].z, player) * cood->pscale1[count].y);
			cood->pw1y[count].b = HEIGHT / 2 - (int)(yaw(cood->pyfloor[count], cood->pt1[count].z, player) * cood->pscale1[count].y);
			cood->pw2y[count].a = HEIGHT / 2 - (int)(yaw(cood->pyceil[count] , cood->pt2[count].z, player) * cood->pscale2[count].y);
			cood->pw2y[count].b = HEIGHT / 2 - (int)(yaw(cood->pyfloor[count], cood->pt2[count].z, player) * cood->pscale2[count].y);
			count++;
		}
		i++;
	}
	//printf("count - %d\n", count);
	cood->piccount = count;
	return (0);
}

int			draw_wall_shots(t_doom *doom, t_player player, t_pics *pic, t_cood *cood)
{
	int		i;
	int		x;
	t_xy	i1;
	t_xy	i2;
	t_xy	ybord;

	doom->isshoot = 1;
	i = 0;
	while (i < doom->num_shots)
	{
		if (pic[i].sector != doom->now.sector)
		{
			i++;
			continue ;
		}
		//printf("i - %d\n", i);
		ybord.y = 0;
		ybord.x = HEIGHT - 1;
		cood->picnum[i] = i;
		cood->pv1[i].x = pic[i].p1.x - player.where.x;
		cood->pv1[i].y = pic[i].p1.y - player.where.y;
		cood->pv2[i].x = pic[i].p2.x - player.where.x;
		cood->pv2[i].y = pic[i].p2.y - player.where.y;
		cood->pt1[i].x = cood->pv1[i].x * player.psin - cood->pv1[i].y * player.pcos;
		cood->pt1[i].z = cood->pv1[i].x * player.pcos + cood->pv1[i].y * player.psin;
		cood->pt2[i].x = cood->pv2[i].x * player.psin - cood->pv2[i].y * player.pcos;
		cood->pt2[i].z = cood->pv2[i].x * player.pcos + cood->pv2[i].y * player.psin;

		if (cood->pt1[i].z <= 0 && cood->pt2[i].z <= 0)
		{
			i++;
			continue ;
		}
		cood->pu0[i] = 0;
		cood->pu1[i] = doom->img[pic[i].images[0][0]].w;
		if (cood->pt1[i].z <= 0 || cood->pt2[i].z <= 0)
		{
			i1 = findintersect(&cood->pt1[i], &cood->pt2[i], -1);
			i2 = findintersect(&cood->pt1[i], &cood->pt2[i], 1);
			cood->porg1[i].x = cood->pt1[i].x;
			cood->porg1[i].y = cood->pt1[i].z;
			cood->porg2[i].x = cood->pt2[i].x;
			cood->porg2[i].y = cood->pt2[i].z;
			if (cood->pt1[i].z < NEARZ)
				iflower(&cood->pt1[i], i1, i2);
			if (cood->pt2[i].z < NEARZ)
				iflower(&cood->pt2[i], i1, i2);
			if (fabs(cood->pt2[i].x - cood->pt1[i].x) > fabs(cood->pt2[i].z - cood->pt1[i].z))
			{
				cood->pu0[i] = (cood->pt1[i].x - cood->porg1[i].x) * cood->pu1[i] / (cood->porg2[i].x - cood->porg1[i].x);
				cood->pu1[i] = (cood->pt2[i].x - cood->porg1[i].x) * cood->pu1[i] / (cood->porg2[i].x - cood->porg1[i].x);
			}
			else
			{
				cood->pu0[i] = (cood->pt1[i].z - cood->porg1[i].y) * cood->pu1[i] / (cood->porg2[i].y - cood->porg1[i].y);
				cood->pu1[i] = (cood->pt2[i].z - cood->porg1[i].y) * cood->pu1[i] / (cood->porg2[i].y - cood->porg1[i].y);
			}
		}
		cood->pscale1[i].x = (HFOV * WIDTH) / cood->pt1[i].z;
		cood->pscale1[i].y = (VFOV * HEIGHT) / cood->pt1[i].z;
		cood->pscale2[i].x = (HFOV * WIDTH) / cood->pt2[i].z;
		cood->pscale2[i].y = (VFOV * HEIGHT) / cood->pt2[i].z;
		cood->pw1x[i] = WIDTH / 2 - (int)(cood->pt1[i].x * cood->pscale1[i].x);
		cood->pw2x[i] = WIDTH / 2 - (int)(cood->pt2[i].x * cood->pscale2[i].x);
		//printf("w1x - %d, w2x - %d\n", cood->pw1x[i], cood->pw2x[i]);
		if (cood->pw1x[i] == cood->pw2x[i])// || cood->pw2x[i] < doom->now.sx || cood->pw1x[i] > doom->now.ex)
		{
			i++;
			continue ;
		}
		cood->pyceil[i] = pic[i].p.z + doom->sectors[doom->now.sector].floor + (float)(doom->img[pic[i].images[0][0]].h) / 10.f - player.where.z;
		cood->pyfloor[i] = pic[i].p.z + doom->sectors[doom->now.sector].floor - player.where.z;
		cood->pw1y[i].a = HEIGHT / 2 - (int)(yaw(cood->pyceil[i] , cood->pt1[i].z, player) * cood->pscale1[i].y);
		cood->pw1y[i].b = HEIGHT / 2 - (int)(yaw(cood->pyfloor[i], cood->pt1[i].z, player) * cood->pscale1[i].y);
		cood->pw2y[i].a = HEIGHT / 2 - (int)(yaw(cood->pyceil[i] , cood->pt2[i].z, player) * cood->pscale2[i].y);
		cood->pw2y[i].b = HEIGHT / 2 - (int)(yaw(cood->pyfloor[i], cood->pt2[i].z, player) * cood->pscale2[i].y);
		x = cood->pw1x[i];
		
		//printf("top - %d, bot - %d\n", doom->item[pic[i].neighbor].ytop[0], doom->item[pic[i].neighbor].ybot[0]);
		while (x <= cood->pw2x[i])
		{
			if (x >= 0 && x < WIDTH)
			{
				if (pic[i].sector != doom->player.sector)
				{
					ybord.y = doom->item[doom->now.sector].ytop[x];
					ybord.x = doom->item[doom->now.sector].ybot[x];
				}
				//printf("w1x - %d, w2x - %d\n", cood->pw1x[i], cood->pw2x[i]);
				cood->ptxtx = (cood->pu0[i] * ((cood->pw2x[i] - x) * cood->pt2[i].z) + cood->pu1[i] * ((x - cood->pw1x[i]) * cood->pt1[i].z)) / ((cood->pw2x[i] - x) * cood->pt2[i].z + (x - cood->pw1x[i]) * cood->pt1[i].z);
				cood->pwy[i].a = (x - cood->pw1x[i]) * (cood->pw2y[i].a - cood->pw1y[i].a) / (cood->pw2x[i] - cood->pw1x[i]) + cood->pw1y[i].a;
				cood->pcy[i].a = clamp(cood->pwy[i].a, ybord.y, ybord.x);
				cood->pwy[i].b = (x - cood->pw1x[i]) * (cood->pw2y[i].b - cood->pw1y[i].b) / (cood->pw2x[i] - cood->pw1x[i]) + cood->pw1y[i].b;
				cood->pcy[i].b = clamp(cood->pwy[i].b, ybord.y, ybord.x);	
				cood->num = cood->picnum[i];
				//if (cood->pcy[i].a > doom->sectors[pic[i].sector].ceil && cood->pcy[i].b < doom->sectors[pic[i].sector].floor)
				//if (cood->pwy[i].a )
				vline3(x, cood->pcy[i], scaler_init(cood->pwy[i], cood->pcy[i].a, 0, doom->img[pic[i].images[0][0]].w), doom);		
				//printf("num - %d\n", cood->picnum[i]);
			}
			x++;
		}
		i++;
	}
	
	doom->isshoot = 0;
	return (0);
}

int			calc_points(t_doom *doom, t_sectors *s, t_cood *cood, t_player player)
{
	find_t_points(s->vert, player, cood);
	if (cood->t1.z <= 0 && cood->t2.z <= 0)
		return (0);
	cood->u0 = 0;
	cood->u1 = (int)sqrt(powf(cood->v1.x - cood->v2.x, 2) + powf(cood->v1.y - cood->v2.y, 2)) / ((s->ceil + s->floor) / 64) * 3;
	
	if (cood->t1.z <= 0 || cood->t2.z <= 0)
	{
		intersect(&cood->t1, &cood->t2, cood);
	}
	
	if (cood->t1.z <= 0.07f)
	{
	//	printf("ok1\n");
		cood->t1.x = (0.07f - cood->t1.z) * (cood->t2.x - cood->t1.x) / (cood->t2.z - cood->t1.z) + cood->t1.x;
		cood->t1.z = 0.07f;
	}
	if (cood->t2.z <= 0.07f)
	{
	//	printf("ok2\n");
		cood->t2.x = (0.07f - cood->t2.z) * (cood->t1.x - cood->t2.x) / (cood->t1.z - cood->t2.z) + cood->t2.x;
		cood->t2.z = 0.07f;
	}
	
	if (!(find_scales(doom, s, cood, player)))
		return (0);
	//printf("aaa \n");
//printf("now sect - %d\n", doom->now.sector);
	calc_pics(doom, doom->pics, &doom->cood, doom->player);
	find_yceil_yfloor(doom, s, cood, player);
	render_walls(doom, s, cood, player);
	
	return (1);
}



int			calc_sector(t_doom *doom, t_sectors *s, t_cood *cood, t_player player)
{
	int		n;

	n = 0;
	while (n < s->npoints)
	{
		cood->n = n;
		if (!(calc_points(doom, s, cood, player)))
		{
			n++;
			continue ;
		}
		n++;
		doom->item[doom->now.sector].ytop = doom->ytop;
		doom->item[doom->now.sector].ybot = doom->ybot;
		if (cood->neighbor >= 0 && cood->endx >= cood->beginx && (doom->head + 32 + 1 - doom->tail) % 32)
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



int			draw_walls(t_doom *doom, t_player player)
{
	int			rensects[doom->num.sectors];
	t_sectors	*s;
	
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
		
		assign_value(doom->item, doom->now, rensects);
		s = &doom->sectors[doom->now.sector];
		calc_sector(doom, s, &doom->cood, doom->player);
		//draw_wall_shots(doom, doom->player, doom->shot_pics, &doom->cood);
		++rensects[doom->now.sector];	
	}
	return (0);
}

int			drawsky(t_doom *doom, t_player player, t_texture *sky, t_img *img)
{
	int		y;
	int		x;
	t_xy 	scale;
	t_xy	t;
	t_img	set;

	set = img[sky[0].image];
	x = 0;
	while (x < WIDTH)
	{
		scale.x = (float)set.w / (WIDTH);
		scale.y = (float)set.h / (HEIGHT);
		t.y = player.yaw * 25;
		t.x = (x * scale.x) + player.angle * 50;
		if (t.x >= set.w)
		{
			while (t.x >= set.w)
				t.x -= set.w;
		}
		else if (t.x < 0)
		{
			while (t.x < 0)
				t.x += set.w;
		}
		y = 0;
		while (y < HEIGHT)
		{
			if (t.y > set.h)
				t.y = set.h - t.y;
			else if (t.y < 0)
				t.y = set.h + t.y;
			if (doom->visible[y][x] == 1)
				doom->sdl->pix[y * WIDTH + x] = set.data[(int)t.y * set.w + (int)t.x];
			t.y += scale.y;
			y++;
		}
		x++;
	}
	return (0);
}

int			draw_scope(t_sdl *sdl)
{
	int		y;
	int		x;
	int		len = 15;
	int		w = 2;

	x = WIDTH / 2 - w;
	while (x < WIDTH / 2 + w)
	{
		y = HEIGHT / 2 - len;
		while (y < HEIGHT / 2 + len)
		{
			sdl->pix[y * WIDTH + x] = 0xFFFFFF;
			y++;	
		}
		x++;
	}
	x = WIDTH / 2 - len;
	while (x < WIDTH / 2 + len)
	{
		y = HEIGHT / 2 - w;
		while (y < HEIGHT / 2 + w)
		{
			sdl->pix[y * WIDTH + x] = 0xFFFFFF;
			y++;	
		}
		x++;
	}
	return (0);
}

int			draw_screen(t_doom *doom)
{	
	draw_walls(doom, doom->player);
	drawsky(doom, doom->player, doom->sky, doom->img);
	drawsprites(doom, doom->objs, doom->player);
	drawweapon(doom, &doom->weapon[doom->player.weapon]);
	draw_scope(doom->sdl);
	drawhud(doom);
	return (0);
}
