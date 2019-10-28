/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_pics.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 18:59:42 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/28 19:13:31 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		render_pics2(t_cood cood, int x, t_pics *pic, t_doom *doom)
{
	t_img	img;

	img = pic_get_image(doom, pic);
	if (x >= cood.w1x && x <= cood.w2x)
	{
		pic->pcood.txtx = (cood.u0 * ((cood.w2x - x) * cood.t2.z) +
		cood.u1 * ((x - cood.w1x) * cood.t1.z)) / ((cood.w2x - x) *
		cood.t2.z + (x - cood.w1x) * cood.t1.z);
		cood.wy.a = (x - cood.w1x) * (cood.w2y.a - cood.w1y.a) /
		(cood.w2x - cood.w1x) + cood.w1y.a;
		cood.cy.a = clamp(cood.wy.a, doom->ytop[x], doom->ybot[x]);
		cood.wy.b = (x - cood.w1x) * (cood.w2y.b - cood.w1y.b) /
		(cood.w2x - cood.w1x) + cood.w1y.b;
		cood.cy.b = clamp(cood.wy.b, doom->ytop[x], doom->ybot[x]);
		vline3(x, cood.cy, scaler_init(cood.wy, cood.cy.a, 0, img.w), doom);
	}
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
		doom->cood.num = i;
		render_pics2(cood, x, &pics[i], doom);
		i++;
	}
	return (0);
}
