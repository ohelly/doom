/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawhud.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:27:54 by glormell          #+#    #+#             */
/*   Updated: 2019/10/30 18:47:23 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			drawhudel(t_hudel e, int *pix)
{
	int			i;
	int			j;
	int			n;
	int			m;

	i = -1;
	while (++i < e.h)
	{
		j = -2;
		while (++j < e.w)
		{
			n = (e.y + i) * WIDTH + e.x + j;
			m = i * e.s->pitch + j * e.s->format->BytesPerPixel;
			if (e.p[m] != 0 && j >= 0)
				pix[n] = e.c;
			else if (e.b && ((j < 0 && e.p[m + 1] != 0) || (j >= 0 &&
					(e.p[m + 1] != 0 || e.p[m - 1] != 0) && j + 1 < e.w &&
					j - 1 >= 0) || ((e.p[m + e.w] != 0 || e.p[m - e.w] != 0) &&
					(i + 1 < e.h && i - 1 >= 0))))
				pix[n] = e.bc;
		}
	}
}

void			drawkey(t_doom *doom, t_obj *key)
{
	int		y;
	int		x;
	t_xy	scale;
	t_xy	t;
	t_img	img;

	img = obj_get_image(doom, key);
	scale.x = (float)img.w / (WIDTH / 5);
	scale.y = (float)img.h / (HEIGHT / 3);
	x = 0;
	while (x < WIDTH / 5)
	{
		t.y = 1;
		t.x = (float)(x - WIDTH / 5) * scale.x;
		y = HEIGHT - HEIGHT / 3 - 200;
		while (y < HEIGHT - 200)
		{
			if (img.data[(int)t.y * img.w + (int)t.x])
				doom->sdl->pix[y * WIDTH + x] =
					img.data[(int)t.y * img.w + (int)t.x];
			t.y += scale.y;
			y++;
		}
		x++;
	}
}

void			drawhud(t_doom *doom)
{
	load_hud(doom);
	drawhudel(doom->hud->health, doom->sdl->pix);
	drawhudel(doom->hud->ammo, doom->sdl->pix);
	if (doom->player.won || doom->player.hp <= 0)
		drawhudel(doom->hud->message, doom->sdl->pix);
	if (doom->player.key)
		drawkey(doom, doom->hud->key);
}
