/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadobjs_collision.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:47:23 by glormell          #+#    #+#             */
/*   Updated: 2019/10/29 01:29:07 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		obj_collision(t_doom *doom, t_xy player)
{
	int		n;
	t_obj	obj;

	n = 0;
	while (n < doom->num.objs)
	{
		obj = doom->objs[n];
		if (obj.col_passable || !obj.enabled)
		{
			n++;
			continue ;
		}
		if (collision_circle(player, doom->player.col_size,
		obj.p, obj.col_size))
			return (0);
		n++;
	}
	return (1);
}

void	obj_collision_key_pickup(t_doom *doom, t_obj *obj)
{
	obj->enabled = 0;
	play_sound(doom, SOUND_PICKUP);
	doom->player.key = 1;
}

void	obj_collision_weapon_pickup(t_doom *doom, t_obj *obj)
{
	int index_offset;

	index_offset = OBJ_TYPE_PISTOL - 1;
	obj->enabled = 0;
	play_sound(doom, SOUND_WEAPON_PICKUP);
	doom->player.allweapons[obj->type - index_offset] = 1;
	doom->player.weapon = obj->type - index_offset;
}

void	obj_collision_ammo_pickup(t_doom *doom, t_obj *obj)
{
	int weapon;
	int ammo;

	if (obj->type == OBJ_TYPE_AMMO_P)
	{
		weapon = 1;
		ammo = 10;
	}
	else if (obj->type == OBJ_TYPE_AMMO_SH)
	{
		weapon = 2;
		ammo = 5;
	}
	else if (obj->type == OBJ_TYPE_AMMO_SMG)
	{
		weapon = 3;
		ammo = 20;
	}
	else
		return ;
	doom->weapon[weapon].ammo += ammo;
	obj->enabled = 0;
	play_sound(doom, SOUND_WEAPON_PICKUP);
}

void	obj_collision_medkit_pickup(t_doom *doom, t_obj *obj)
{
	int hp;

	if (obj->type == OBJ_TYPE_MED_SMALL)
		hp = 10;
	else if (obj->type == OBJ_TYPE_MED_MEDIUM)
		hp = 30;
	else if (obj->type == OBJ_TYPE_MED_BIG)
		hp = 60;
	if (doom->player.hp < 100)
	{
		obj->enabled = 0;
		play_sound(doom, SOUND_PICKUP);
		doom->player.hp += hp;
		if (doom->player.hp > 100)
			doom->player.hp = 100;
	}
}
