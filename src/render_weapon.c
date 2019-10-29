/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_weapon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:58:37 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/29 17:45:40 by dtoy             ###   ########.fr       */
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
		t.y = 0;
		t.x = (x - WIDTH) * scale.x;
		y = 0 + doom->shakey;
		while (y < HEIGHT)
		{
			if ((int)t.y >= 0 && (int)t.y <= img.h &&
			(int)t.x >= 0 && (int)t.x <= img.w)
			{
				if (img.data[(int)t.y * img.w + (int)t.x])
					pix[y * WIDTH + x] =
						img.data[(int)t.y * img.w + (int)t.x];
			}
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

	printf("1\n");
	img = wpn_get_image(doom, wpn);
	printf("2\n");
	scale.x = (float)img.w / (WIDTH - WIDTH / 4);
	scale.y = (float)img.h / (HEIGHT);
	render_weapon2(doom, scale, img, doom->sdl->pix);
	printf("3\n");
	return (0);
}
