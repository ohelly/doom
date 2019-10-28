/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vlineobj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 17:24:38 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/28 18:53:09 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	check_scatter_obj(int x, int y, t_obj *obj, t_doom *doom)
{
	if (obj->on_hit != NULL &&
		x >= WIDTH / 2 - doom->weapon[doom->player.weapon].scatterx &&
		x <= WIDTH / 2 + doom->weapon[doom->player.weapon].scatterx &&
		y >= HEIGHT / 2 - doom->weapon[doom->player.weapon].scattery &&
		y <= HEIGHT / 2 + doom->weapon[doom->player.weapon].scattery)
		doom->obj_ind[doom->obj_num] = 1;
}

void	find_ybord(t_xy *ybord, t_obj *obj, t_doom *doom, t_be px)
{
	ybord->y = 0;
	ybord->x = HEIGHT - 1;
	if (obj->sector != doom->player.sector)
	{
		ybord->y = doom->item[obj->sector].ytop[px.x];
		ybord->x = doom->item[obj->sector].ybot[px.x];
	}
}

void	vlineobj(t_be px, t_ab_i wy, t_obj *obj, t_doom *doom)
{
	t_xy	scale;
	t_xy	t;
	t_xy	ybord;
	t_img	img;
	int		color;

	img = obj_get_image(doom, obj);
	scale.x = (float)img.w / (px.end - px.begin);
	scale.y = (float)img.h / (wy.b - wy.a);
	t.x = (px.x - px.begin) * scale.x;
	t.y = 1;
	find_ybord(&ybord, obj, doom, px);
	while (wy.a <= wy.b)
	{
		color = img.data[(int)t.y * img.w + (int)t.x];
		if (t.x < img.w && t.y < img.h && color
		&& wy.a >= ybord.y && wy.a <= ybord.x)
		{
			check_scatter_obj(px.x, wy.a, obj, doom);
			doom->sdl->pix[wy.a * WIDTH + px.x] =
			check_light(color, &doom->sectors[obj->sector]);
		}
		wy.a++;
		t.y += scale.y;
	}
}
