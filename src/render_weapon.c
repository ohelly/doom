/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_weapon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:58:37 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/29 18:57:39 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		render_weapon2(t_doom *doom, t_xy scale, t_img img, int *pix)
{
	int		x;
	int		y;
	t_xy	t;
	int		index;

	x = WIDTH - (img.w / scale.x);
	t.x = 0;
	while (x < WIDTH)
	{
		t.y = 0;
		y = (HEIGHT - (img.h / scale.y)) + doom->shakey;
		while (y < HEIGHT)
		{
			x = CLAMP(x, 0, WIDTH - 1);
			index = (int)t.x + (int)t.y * img.w;
			if (img.data[index])
				pix[x + CLAMP(y, 0, HEIGHT - 1) * WIDTH] = img.data[index];
			t.y += scale.y;
			y++;
		}
		t.x += scale.x;
		x++;
	}
}

int			render_weapon(t_doom *doom, t_weapon *wpn)
{
	t_xy	scale;
	t_img	img;

	img = wpn_get_image(doom, wpn);
	scale.x = (float)img.w / (HEIGHT * 1.2f);
	scale.y = (float)img.h / (HEIGHT * 1.2f);
	if (!doom->player.weapon &&
	doom->weapon[doom->player.weapon].states_frame == 0)
		return (0);
	render_weapon2(doom, scale, img, doom->sdl->pix);
	return (0);
}
