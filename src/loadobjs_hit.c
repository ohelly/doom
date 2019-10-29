/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadobjs_hit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 21:13:01 by glormell          #+#    #+#             */
/*   Updated: 2019/10/29 17:38:23 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		find_obj_interaction(t_doom *doom)
{
	int		n;
	t_obj	*obj;
	t_xy	p;
	t_xy	d;

	p = (t_xy){doom->player.where.x, doom->player.where.y};
	d = (t_xy){doom->player.pcos * 4, doom->player.psin * 4};
	n = 0;
	while (n < doom->num.objs)
	{
		obj = &doom->objs[n];
		if (!obj->enabled || obj->on_interaction == NULL)
		{
			n++;
			continue ;
		}
		if (collision_box(p, v2_add(p, d), v2_addf(obj->p, -obj->col_size),
		v2_addf(obj->p, obj->col_size)))
		{
			obj->on_interaction(doom, obj);
			return (1);
		}
		n++;
	}
	return (0);
}

void	obj_anim_end_disable(t_obj *obj)
{
	obj->enabled = 0;
}

void	obj_hit_explosive(t_doom *doom, t_obj *obj)
{
	int		i;
	t_obj	*o;

	play_sound(doom, SOUND_EXPLOSIVE);
	obj_state_change(obj, 1);
	obj->on_anim_end = obj_anim_end_disable;
	obj->on_hit = NULL;
	i = 0;
	while (i < doom->num.objs)
	{
		o = &doom->objs[i];
		if (o->enabled && obj->n != i && o->on_hit != NULL &&
			distance(o->p, obj->p) < 20.0f)
			o->on_hit(doom, o);
		i++;
	}
}

void	obj_hit_breakable(t_doom *doom, t_obj *obj)
{
	doom->a = doom->a;
	obj_state_change(obj, 1);
}
