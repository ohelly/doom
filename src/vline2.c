/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vline2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:21:28 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/27 20:21:55 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
