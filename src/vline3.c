/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vline3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:22:03 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/29 01:55:39 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	check_scatter(int x, int y, t_weapon weapon, t_doom *doom)
{
	if (x >= WIDTH / 2 - weapon.scatterx &&
		x <= WIDTH / 2 + weapon.scatterx &&
		y >= HEIGHT / 2 - weapon.scattery &&
		y <= HEIGHT / 2 + weapon.scattery &&
		doom->cood.num < doom->num.objs)
		doom->pic_interaction[doom->cood.num] = 1;
}

void	vline3(int x, t_ab_i wy, t_scaler ty, t_doom *doom)
{
	int			txty;
	t_py_i		p;
	t_sectors	*s;
	int			color;
	t_img		img;

	p.y1 = CLAMP(wy.a, 0, HEIGHT - 1);
	p.y2 = CLAMP(wy.b, 0, HEIGHT - 1);
	s = &doom->sectors[doom->now.sector];
	img = pic_get_image(doom, &doom->pics[doom->cood.num]);
	while (p.y1 <= p.y2)
	{
		txty = scaler_next(&ty);
		color = img.data[txty % img.h * img.w +
		doom->pics[doom->cood.num].pcood.txtx % img.w];
		if (color)
		{
			check_scatter(x, p.y1, doom->weapon[doom->player.weapon], doom);
			doom->sdl->pix[p.y1 * WIDTH + x] = check_light(color, s);
		}
		p.y1++;
	}
}
