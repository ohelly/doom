/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawobj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 17:38:08 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/30 16:35:05 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			renobj(t_be px, t_ab_i wy, t_obj *obj, t_doom *doom)
{
	px.x = px.begin;
	while (px.x <= px.end)
	{
		if (px.x >= doom->item[obj->sector].sx &&
		px.x <= doom->item[obj->sector].ex)
			vlineobj(px, wy, obj, doom);
		px.x++;
	}
	return (0);
}

int			findobjxy2(t_xyz t, t_xy scale, t_obj *obj, t_doom *doom)
{
	int		wx;
	t_xy	size;
	t_ab_i	wy;
	t_be	px;
	t_img	img;

	img = obj_get_image(doom, obj);
	size.y = img.h / 17.0f * obj->scale;
	size.x = img.w / 57.0f * obj->scale;
	wx = WIDTH / 2 - (int)(t.x * scale.x);
	wy.a = HEIGHT / 2 - (int)(yaw(size.y + doom->sectors[obj->sector].floor -
	doom->player.where.z, t.z, doom->player) * scale.y);
	wy.b = HEIGHT / 2 - (int)(yaw(doom->sectors[obj->sector].floor -
	doom->player.where.z, t.z, doom->player) * scale.y);
	size.x = size.x * scale.x;
	px.begin = wx - size.x / 2;
	px.end = wx + size.x / 2;
	renobj(px, wy, obj, doom);
	return (0);
}

int			drawobj(t_doom *doom, t_obj *obj)
{
	t_xy	v;
	t_xyz	t;
	t_xy	scale;

	if (obj->enabled == 0)
		return (0);
	v.x = obj->p.x - doom->player.where.x;
	v.y = obj->p.y - doom->player.where.y;
	t.x = v.x * doom->player.psin - v.y * doom->player.pcos;
	t.z = v.x * doom->player.pcos + v.y * doom->player.psin;
	if (obj->anim_count[obj->states_frame] > 1)
		if (doom->a == 1)
			obj_anim_next(obj);
	if (t.z <= 0)
		return (0);
	scale.x = (HFOV * WIDTH) / t.z;
	scale.y = (VFOV * HEIGHT) / t.z;
	findobjxy2(t, scale, obj, doom);
	return (1);
}
