/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_triggers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:23:48 by njacobso          #+#    #+#             */
/*   Updated: 2019/10/23 17:24:00 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	on_collision_key(t_doom *doom, t_obj *obj)
{
	if (obj->enabled == 0)
		return ;
	obj->enabled = 0;
	printf("obj %d has been triggered\n", obj->id);
}

int		check_player_collision(t_doom *doom, t_obj *obj)
{
	t_xy pl;
	t_xy pos;

	pl = (t_xy){doom->player.where.x, doom->player.where.y};
	pos = obj->p;
	if (collision_circle(pl, doom->player.col_size, pos, obj->col_size))
		return (1);
	return (0);
}

int		objects_update(t_doom *doom)
{
	int		i;
	t_obj	*o;

	i = 0;
	while (i < doom->num.objs)
	{
		o = &doom->objs[i];
		if (o->enabled)
		{
			if (o->on_collision != NULL)
				if (check_player_collision(doom, o))
					o->on_collision(doom, o);
		}
		i++;
	}
	return (0);
}
