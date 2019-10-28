/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_interact.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 19:49:33 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/28 19:50:25 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		find_door(t_doom *doom, t_player player)
{
	t_sectors	*s;
	t_xy		*v;
	int			n;
	t_xy		p;
	t_xy		d;

	p = (t_xy){player.where.x, player.where.y};
	d = (t_xy){player.pcos * 8, player.psin * 8};
	s = &doom->sectors[player.sector];
	if (s->type == 2 && !player.key)
		return (0);
	v = s->vert;
	n = 0;
	while (n < s->npoints)
	{
		if (s->neighbors[n] >= 0 && collision_box_dir(p,
		v2_add(p, d), v[n], v[n + 1]))
		{
			doom->sectors[s->neighbors[n]].active = 1;
			return (1);
		}
		n++;
	}
	return (0);
}

void	change_light(t_player player, t_sectors *s, t_pics *pic)
{
	static int t = 0;

	if (t == 0)
	{
		s->light = 15 / 100.f;
		pic->states_frame = 1;
		t = 1;
	}
	else
	{
		s->light = 80 / 100.f;
		pic->states_frame = 0;
		t = 0;
	}
}

int		find_pic_interaction(t_doom *doom, t_player player, t_pics *pics)
{
	int		i;

	i = 0;
	while (i < doom->num.pics)
	{
		if (doom->pic_interaction[i] == 1)
		{
			if (sqrt(pow(player.where.x - pics[i].p.x, 2) +
			pow(player.where.y - pics[i].p.y, 2)) > 10 && !player.weapon)
				return (0);
			if (pics[i].type == PIC_TYPE_SWITCH)
				change_light(player, &doom->sectors[player.sector], &pics[i]);
			if (pics[i].type == PIC_TYPE_DECOR && doom->lkey)
			{
				play_sound(doom, SOUND_CRASH);
				pics[i].states_frame = 1;
				pics[i].anim_frame = 0;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int		find_on_hit_obj(t_doom *doom)
{
	int		j;
	int		t;

	t = 0;
	j = 0;
	while (j < doom->num.objs)
	{
		if (t == 3)
			return (t);
		if (doom->obj_ind[j] == 1 && doom->objs[j].on_hit != NULL)
		{
			if (!doom->player.weapon
			&& sqrt(pow(doom->player.where.x - doom->objs[j].p.x, 2) +
			pow(doom->player.where.y - doom->objs[j].p.y, 2)) > 10)
				return (0);
			doom->objs[j].on_hit(doom, &doom->objs[j]);
			t++;
		}
		j++;
	}
	return (t);
}
