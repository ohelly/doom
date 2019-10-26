/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawsprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 11:56:24 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/26 14:53:07 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			findobjslen(t_doom *doom, t_obj *obj, float *len, t_player player)
{
	int		n;

	n = 0;
    while (n < doom->num.objs)
	{
		len[n] = sqrtf(powf(obj[n].p.x - player.where.x, 2) + powf(obj[n].p.y - player.where.y, 2));
		n++;
	}
	return (0);
}

int			*sortobjs(t_doom *doom, int *order, t_player player)
{
	int		n;
	int		j;
	float	l;
	float	len[doom->num.objs];
	int		tmp;

	findobjslen(doom, doom->objs, len, player);
	ft_memmove(doom->len, len, doom->num.objs * 4);
	j = 0;
	while (j < doom->num.objs)
	{
		order[j] = j;
		j++;
	}
	j = 0;
	n = 0;
	while (j < doom->num.objs)
	{
		n = 0;
		while (n < doom->num.objs - 1)
		{
			if (len[n] < len[n + 1])
			{
				tmp = order[n + 1];
				order[n + 1] = order[n];
				order[n] = tmp;
				l = len[n + 1];
				len[n + 1] = len[n];
				len[n] = l;
			}
			n++;
		}
		j++;
	}
	return (order);
}

int		vlineobj(t_be px, t_ab_i wy, t_obj *obj, t_doom *doom)
{
	t_xy	scale;
	t_xy	t;
	t_xy	ybord;	//ybot, ytop
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

int		renobj(t_be px, t_ab_i wy, t_obj *obj, t_doom *doom)
{
	px.x = px.begin;
	while (px.x < px.end)
	{
		if (px.x >= doom->item[obj->sector].sx && px.x < doom->item[obj->sector].ex)
			vlineobj(px, wy, obj, doom);
		px.x++;
	}
	return (0);
}

int		findobjxy2(t_xyz t, t_xy scale, t_obj *obj, t_doom *doom)
{
	int		wx;
	t_xy	size;	//w, h
	t_ab_i	wy;
	t_be	px;
	t_img	img;

	img = obj_get_image(doom, obj);
	size.y = img.h / 17.0f * obj->scale;
	size.x = img.w / 57.0f * obj->scale;
	wx = WIDTH / 2 - (int)(t.x * scale.x); 
	wy.a = HEIGHT / 2 - (int)(yaw(size.y + doom->sectors[obj->sector].floor - doom->player.where.z, t.z, doom->player) * scale.y); 
	wy.b = HEIGHT / 2 - (int)(yaw(doom->sectors[obj->sector].floor - doom->player.where.z, t.z, doom->player) * scale.y);
	size.x = size.x * scale.x;
	px.begin = wx - size.x / 2;
	px.end = wx + size.x / 2;
	renobj(px, wy, obj, doom);
	return (0);
}

int      drawobj(t_doom *doom, t_obj *obj, t_xy pos)
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
	{
		if (doom->a == 1)
			obj_anim_next(obj);
	}
	if (t.z <= 0)
		return (0);
	scale.x = (HFOV * WIDTH) / t.z;
	scale.y = (VFOV * HEIGHT) / t.z;
	findobjxy2(t, scale, obj, doom);
    return (1);
}

int     drawsprites(t_doom *doom, t_obj *obj, t_player player)
{
    int     n;
    t_obj   *o;
	int		*order;
	int		j;

	j = 0;
	while (j < 32)
	{
		doom->obj_ind[j] = 0;
		j++;
	}
	order = (int*)malloc(sizeof(int) * doom->num.objs);
    sortobjs(doom, order, doom->player);
    n = 0;
    while (n < doom->num.objs)
    {
        o = &doom->objs[order[n]];
		doom->obj_num = o->n;
		if (!doom->item[o->sector].sector || doom->len[n] < 3.f)
		{
			n++;
			continue ;
		}
        if (!(drawobj(doom, o, o->p)))
		{
			n++;
			continue ;
		}
        n++;
    }
	free(order);
    return (0);
}
