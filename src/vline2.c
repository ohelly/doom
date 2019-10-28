/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vline2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:21:28 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/29 00:32:15 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	vline2(int x, t_ab_i wy, t_scaler ty, t_doom *doom)
{
	int			txty;
	t_py_i		p;
	int			color;
	t_sectors	*s;
	t_img		img;

	p.y1 = clamp(wy.a, 0, HEIGHT - 1);
	p.y2 = clamp(wy.b, 0, HEIGHT - 1);
	s = &doom->sectors[doom->now.sector];
	img = doom->img[doom->walls[s->txtw[doom->cood.n]].image];
	while (p.y1 < p.y2)
	{
		if (doom->cood.neighbor == -2 && p.y1 != doom->ybot[x])
		{
			doom->visible[p.y1][x] = 1;
			p.y1++;
			continue ;
		}
		txty = scaler_next(&ty);
		color = img.data[txty % img.h * img.w + doom->cood.txtx % img.w];
		doom->sdl->pix[p.y1 * WIDTH + x] = check_light(color, s);
		p.y1++;
	}
}
