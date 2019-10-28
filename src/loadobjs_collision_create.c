/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadobjs_collision_create.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:54:11 by glormell          #+#    #+#             */
/*   Updated: 2019/10/29 01:28:03 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	create_obj_key(t_doom *doom, t_obj *obj)
{
	obj->col_passable = 1;
	obj->col_size = 3.0f;
	obj->on_collision = obj_collision_key_pickup;
	doom->a = doom->a;
}

void	create_obj_weapon(t_doom *doom, t_obj *obj)
{
	obj->col_passable = 1;
	obj->col_size = 3.0f;
	obj->on_collision = obj_collision_weapon_pickup;
	doom->a = doom->a;
}

void	create_obj_ammo(t_doom *doom, t_obj *obj)
{
	obj->col_passable = 1;
	obj->col_size = 3.0f;
	obj->on_collision = obj_collision_ammo_pickup;
	doom->a = doom->a;
}

void	create_obj_medkit(t_doom *doom, t_obj *obj)
{
	obj->col_passable = 1;
	obj->col_size = 3.0f;
	obj->on_collision = obj_collision_medkit_pickup;
	doom->a = doom->a;
}
