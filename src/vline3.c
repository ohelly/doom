/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vline3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:22:03 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/27 20:22:09 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
	set = pic_get_image(doom, &doom->pics[doom->cood.num]);
    while (y <= y2)
    {
        txty = scaler_next(&ty);
		color = set.data[txty % set.h * set.w + doom->pics[doom->cood.num].pcood.txtx % set.w];
		if (color)
		{
			if (x >= WIDTH / 2 - doom->weapon[doom->player.weapon].scatterx &&
				x <= WIDTH / 2 + doom->weapon[doom->player.weapon].scatterx &&
				y >= HEIGHT / 2 - doom->weapon[doom->player.weapon].scattery &&
				y <= HEIGHT / 2 + doom->weapon[doom->player.weapon].scattery && doom->cood.num < 64)
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
