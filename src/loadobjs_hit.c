/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadobjs_hit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 21:13:01 by glormell          #+#    #+#             */
/*   Updated: 2019/10/28 21:15:36 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
	i = 0;
	while (i < doom->num.objs)
	{
		o = &doom->objs[i];
		if (obj->n != i && o->on_hit != NULL && distance(o->p, obj->p) < 20.0f)
			o->on_hit(doom, o);
		i++;
	}
}

void	obj_hit_breakable(t_doom *doom, t_obj *obj)
{
	obj_state_change(obj, 1);
}
