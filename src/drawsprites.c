/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawsprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 11:56:24 by dtoy              #+#    #+#             */
/*   Updated: 2019/09/29 17:26:25 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			findobjslen(t_doom *doom, t_obj *obj, float *len, t_player player)
{
	int		n;

	n = 0;
    while (n < doom->numobjs)
	{
		len[n] = sqrtf(powf(obj[n].p.x - player.where.x, 2) + powf(obj[n].p.y - player.where.y, 2));
		n++;
	}
	return (0);
}

int			sortobjs(t_doom *doom, t_obj *obj, t_player player)
{
    int     n;
    int     j;
    float   l;
    float   len[doom->numobjs];
    t_obj   tmp;
    
	findobjslen(doom, obj, len, player);
	n = 0;
	j = 0;
	while (j < doom->numobjs)
	{
		n = 0;
		while (n < doom->numobjs - 1)
		{
			if (len[n] < len[n + 1])
			{
				tmp = obj[n + 1];
				obj[n + 1] = obj[n];
				obj[n] = tmp;
				l = len[n + 1];
				len[n + 1] = len[n];
				len[n] = l;
			}
			n++;
		}
		j++;
	}
    return (0);
}

int		vlineobj(t_be px, t_ab_i wy, t_obj *obj, t_doom *doom)
{
	t_xy	scale;
	t_xy	t;
	int		ytop;
	int		ybot;
	int		y;

	t.y = 0;
	scale.x = (float)obj->img.w / (px.end - px.begin);
	scale.y = (float)obj->img.h / (wy.b - wy.a);
	t.x = (px.x - px.begin) * scale.x;
	y = wy.a;
	if (obj->sector != doom->player.sector)
	{
		ytop = doom->item[obj->sector].ytop[px.x];
		ybot = doom->item[obj->sector].ybot[px.x];
	}
	else
	{
		ytop = 0;
		ybot = HEIGHT - 1;
	}
	while (y < wy.b)
	{
		if (t.x < obj->img.w && t.y < obj->img.h && obj->img.data[0][(int)t.y * obj->img.w + (int)t.x] && y >= ytop && y <= ybot) //0 is num of animation frame
			doom->sdl->pix[y * WIDTH + px.x] = obj->img.data[0][(int)t.y * obj->img.w + (int)t.x];
		y++;
		t.y += scale.y;
	}
	return (0);
}

int		renobj(t_be px, t_ab_i wy, t_obj *obj, t_doom *doom)
{
	px.x = px.begin;
	while(px.x < px.end)
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
	float	h;
	float	w;
	t_ab_i	wy;
	t_be	x;
	
	h = (float)(obj->img.h / 28);
	w = (float)(obj->img.w / 100);
	wx = WIDTH / 2 - (int)(t.x * scale.x); 
	wy.a = HEIGHT / 2 - (int)(yaw(h + doom->sector[obj->sector].floor - doom->player.where.z, t.z, doom->player) * scale.y); 
	wy.b = HEIGHT / 2 - (int)(yaw(doom->sector[obj->sector].floor - doom->player.where.z, t.z, doom->player) * scale.y);
	w = w * scale.x;
	x.begin = wx - w / 2;
	x.end = wx + w / 2;
	renobj(x, wy, obj, doom);
	return (0);
}

int      drawobj(float x, float y, t_obj *obj, t_doom *doom)
{
    t_xy	v;
	t_xyz	t;
	t_xy	scale;

	v.x = obj->p.x - doom->player.where.x;
	v.y = obj->p.y - doom->player.where.y;
	t.x = v.x * doom->player.anglesin - v.y * doom->player.anglecos;
	t.z = v.x * doom->player.anglecos + v.y * doom->player.anglesin;
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

    sortobjs(doom, doom->obj, doom->player);
    n = 0;
    while (n < doom->numobjs)
    {
        o = &obj[n];
		if (!doom->item[obj->sector].sector)
		{
			n++;
			continue ;
		}
        if (!(drawobj(obj->p.x, obj->p.y, o, doom)))
		{
			n++;
			continue ;
		}
        n++;
    }
    return (0);
}
