/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:19:28 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/27 20:58:27 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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

int			render_pics(t_doom *doom, t_pics *pics, int x) 
{
	int		i;
	t_img	img;
	t_cood	cood;

	i = 0;
	while (i < doom->num.pics + doom->num_shots)
	{
		if (pics[i].vis == 0)
		{
			i++;
			continue ;
		}
		cood = pics[i].pcood;
		img = pic_get_image(doom, &pics[i]);
		if (x >= cood.w1x && x <= cood.w2x)
		{
			pics[i].pcood.txtx = (cood.u0 * ((cood.w2x - x) * cood.t2.z) + cood.u1 * ((x - cood.w1x) * cood.t1.z)) / ((cood.w2x - x) * cood.t2.z + (x - cood.w1x) * cood.t1.z);
			cood.wy.a = (x - cood.w1x) * (cood.w2y.a - cood.w1y.a) / (cood.w2x - cood.w1x) + cood.w1y.a;
			cood.cy.a = clamp(cood.wy.a, doom->ytop[x], doom->ybot[x]);
			cood.wy.b = (x - cood.w1x) * (cood.w2y.b - cood.w1y.b) / (cood.w2x - cood.w1x) + cood.w1y.b;
			cood.cy.b = clamp(cood.wy.b, doom->ytop[x], doom->ybot[x]);
			doom->cood.num = i;
			vline3(x, cood.cy, scaler_init(cood.wy, cood.cy.a, 0, img.w), doom);		
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
		render_pics(doom, doom->pics, x);
		x++;
	}
	return (0);
}
