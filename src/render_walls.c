/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 18:59:19 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/29 12:54:59 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		clamp_ny(t_doom *doom, t_cood *cood)
{
	cood->ny.a = (cood->x - cood->w1x) * (cood->n2y.a - cood->n1y.a) /
	(cood->w2x - cood->w1x) + cood->n1y.a;
	cood->cny.a = CLAMP(cood->ny.a, doom->ytop[cood->x], doom->ybot[cood->x]);
	cood->ny.b = (cood->x - cood->w1x) * (cood->n2y.b - cood->n1y.b) /
	(cood->w2x - cood->w1x) + cood->n1y.b;
	cood->cny.b = CLAMP(cood->ny.b, doom->ytop[cood->x], doom->ybot[cood->x]);
}

void		render_walls2(t_doom *doom, t_sectors *s,
t_cood *cood)
{
	t_ab_i	scaler;

	if (cood->neighbor >= 0)
	{
		clamp_ny(doom, cood);
		scaler.a = cood->cy.a;
		scaler.b = cood->cny.a - 1;
		vline2(cood->x, scaler, scaler_init(cood->wy, cood->cy.a, 0,
		doom->img[doom->walls[s->txtw[cood->n]].image].w), doom);
		doom->item[doom->now.sector].ytop[cood->x] = CLAMP(MAX(cood->cny.a, cood->cy.a), 0, HEIGHT - 1);
		doom->ytop[cood->x] = CLAMP(MAX(cood->cy.a, cood->cny.a - 1),
		doom->ytop[cood->x], HEIGHT - 1);
		scaler.a = cood->cny.b;
		scaler.b = cood->cy.b;
		vline2(cood->x, scaler, scaler_init(cood->wy, cood->cny.b, 0,
		doom->img[doom->walls[s->txtw[cood->n]].image].w), doom);
		doom->item[doom->now.sector].ybot[cood->x] = CLAMP(MIN(cood->cny.b, cood->cy.b), 0, HEIGHT - 1);
		doom->ybot[cood->x] = CLAMP(MIN(cood->cy.b, cood->cny.b), 0,
		doom->ybot[cood->x]);
	}
	else
	{
		vline2(cood->x, cood->cy, scaler_init(cood->wy, cood->cy.a, 0,
		doom->img[doom->walls[s->txtw[cood->n]].image].w), doom);
		//printf("cood->x - %d\n", cood->x);
		doom->item[doom->now.sector].ytop[cood->x] = CLAMP(cood->cy.a, 0, HEIGHT - 1);
		doom->item[doom->now.sector].ybot[cood->x] = CLAMP(cood->cy.b, 0, HEIGHT - 1);
	}
}

void		render_walls(t_doom *doom, t_sectors *s,
t_cood *cood, t_player player)
{
	int		x;

	cood->beginx = MAX(cood->w1x, doom->now.sx);
	cood->endx = MIN(cood->w2x, doom->now.ex);
	x = cood->beginx - 1;
	while (++x <= cood->endx)
	{
		if (x == WIDTH / 2)
			doom->lookwall[doom->now.sector] = cood->n;
		cood->x = x;
		cood->txtx = (cood->u0 * ((cood->w2x - x) * cood->t2.z) +
		cood->u1 * ((x - cood->w1x) * cood->t1.z)) / ((cood->w2x - x) *
		cood->t2.z + (x - cood->w1x) * cood->t1.z);
		cood->wy.a = (x - cood->w1x) * (cood->w2y.a - cood->w1y.a) /
		(cood->w2x - cood->w1x) + cood->w1y.a;
		cood->cy.a = CLAMP(cood->wy.a, doom->ytop[x], doom->ybot[x]);
		cood->wy.b = (x - cood->w1x) * (cood->w2y.b - cood->w1y.b) /
		(cood->w2x - cood->w1x) + cood->w1y.b;
		cood->cy.b = CLAMP(cood->wy.b, doom->ytop[x], doom->ybot[x]);
		draw_ceil_floor(doom, s, cood, player);
		render_walls2(doom, s, cood);
		render_pics(doom, doom->pics, x);
	}
}
