/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vlineobj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 17:24:38 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/28 17:24:57 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		vlineobj(t_be px, t_ab_i wy, t_obj *obj, t_doom *doom)
{
	t_xy	scale;
	t_xy	t;
	t_xy	ybord;
	int		y;
	t_img	img;
	int		color;
	int		prev_color;
	int		prev_light;

	img = obj_get_image(doom, obj);
	t.y = 1;
	ybord.y = 0;
	ybord.x = HEIGHT - 1;
	scale.x = (float)img.w / (px.end - px.begin);
	scale.y = (float)img.h / (wy.b - wy.a);
	t.x = (px.x - px.begin) * scale.x;
	y = wy.a;
	if (obj->sector != doom->player.sector)
	{
		ybord.y = doom->item[obj->sector].ytop[px.x];
		ybord.x = doom->item[obj->sector].ybot[px.x];
	}
	prev_light = 0;
	prev_color = 0;
	while (y < wy.b)
	{
		color = img.data[(int)t.y * img.w + (int)t.x];
		if (t.x < img.w && t.y < img.h && color && y >= ybord.y && y <= ybord.x) //0 is num of animation frame
		{
			if (prev_color != color)
			{
				prev_color = color;
				prev_light = rgb_multiply(color, doom->sectors[obj->sector].light);
			}
			if (obj->on_hit != NULL && px.x >= WIDTH / 2 - doom->weapon[doom->player.weapon].scatterx &&
			px.x <= WIDTH / 2 + doom->weapon[doom->player.weapon].scatterx &&
			y >= HEIGHT / 2 - doom->weapon[doom->player.weapon].scattery &&
			y <= HEIGHT / 2 + doom->weapon[doom->player.weapon].scattery)
				doom->obj_ind[doom->obj_num] = 1;
			doom->sdl->pix[y * WIDTH + px.x] = prev_light;
		}
		y++;
		t.y += scale.y;
	}
	return (0);
}
