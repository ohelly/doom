/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawsky.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:13:40 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/29 01:00:14 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		cut_txt_w(t_xy *t, int w)
{
	if (t->x >= w)
	{
		while (t->x >= w)
			t->x -= w;
	}
	else if (t->x < 0)
	{
		while (t->x < 0)
			t->x += w;
	}
}

void		cut_txt_y(t_xy *t, int h)
{
	if (t->y > h)
	{
		while (t->y > h)
			t->y = h - t->y;
	}
	else if (t->y < 0)
	{
		while (t->y < 0)
			t->y = h + t->y;
	}
}

void		drawsky(t_doom *doom, t_player player, t_texture *sky, t_img *img)
{
	int		y;
	int		x;
	t_xy	scale;
	t_xy	t;
	t_img	set;

	set = img[sky[0].image];
	scale.x = (float)set.w / (WIDTH);
	scale.y = (float)set.h / (HEIGHT);
	x = -1;
	while (++x < WIDTH)
	{
		t.y = player.yaw * 25;
		t.x = (x * scale.x) + player.angle * 50;
		cut_txt_w(&t, set.w);
		y = -1;
		while (++y < HEIGHT)
		{
			cut_txt_y(&t, set.h);
			if (doom->visible[y][x] == 1)
				doom->sdl->pix[y * WIDTH + x] =
				set.data[(int)t.y * set.w + (int)t.x];
			t.y += scale.y;
		}
	}
}
