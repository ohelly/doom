/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_weapon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:58:37 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/27 21:02:30 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		render_weapon2(t_doom *doom, t_xy scale, t_img img, int *pix)
{
	int		y;
	int		x;
	t_xy	t;

	x = WIDTH / 4;
	while (x < WIDTH)
	{
		t.y = 1;
		t.x = (x - WIDTH) * scale.x;
		y = 0 + doom->shakey;
		while (y < HEIGHT)
		{
			if (img.data[(int)t.y * img.w + (int)t.x])
				pix[y * WIDTH + x] =
					img.data[(int)t.y * img.w + (int)t.x];
			t.y += scale.y;
			y++;
		}
		x++;
	}
}

int			render_weapon(t_doom *doom, t_weapon *wpn)
{
	t_xy	scale;
	t_img	img;

	img = wpn_get_image(doom, wpn);
	scale.x = (float)img.w / (WIDTH - WIDTH / 4);
	scale.y = (float)img.h / (HEIGHT);
	render_weapon2(doom, scale, img, doom->sdl->pix);
	return (0);
}
