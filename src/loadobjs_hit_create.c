/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadobjs_hit_create.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 21:07:12 by glormell          #+#    #+#             */
/*   Updated: 2019/10/29 01:20:36 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		create_obj_decor(t_doom *doom, t_obj *obj)
{
	obj->col_passable = 1;
	obj->col_size = 0.1f;
	doom->a = doom->a;
	return (0);
}

int		create_obj_explosive(t_doom *doom, t_obj *obj)
{
	obj->col_passable = 0;
	obj->col_size = 3.0f;
	obj->on_hit = obj_hit_explosive;
	doom->a = doom->a;
	return (0);
}

int		create_obj_enemy_default(t_doom *doom, t_obj *obj)
{
	obj->col_passable = 1;
	obj->col_size = 5.0f;
	obj->scale = 6.0f;
	create_enemy_default(doom, obj);
	return (0);
}

int		create_obj_box(t_doom *doom, t_obj *obj)
{
	obj->col_passable = 0;
	obj->col_size = 3.0f;
	doom->a = doom->a;
	return (0);
}

int		create_obj_breakable(t_doom *doom, t_obj *obj)
{
	obj->col_passable = 0;
	obj->col_size = 3.0f;
	obj->on_hit = obj_hit_breakable;
	doom->a = doom->a;
	return (0);
}
