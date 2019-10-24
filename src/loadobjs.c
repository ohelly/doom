/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadobjs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 12:50:34 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/24 18:24:26 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	obj_state_change(t_obj *obj, int state)
{
	if (state >= obj->states_count || state < 0 || state == obj->states_frame)
		return ;
	obj->states_frame = state;
	obj->anim_frame = 0;
}

void	obj_anim_next(t_obj *obj)
{
	int index;
	int state;
	int anim_frame;

	state = obj->states_frame;
	if (obj->anim_count[state] <= 1)
		return ;
	obj->anim_frame++;
	if (obj->anim_frame >= obj->anim_count[state] || obj->images[state][obj->anim_frame] == -1)
		obj->anim_frame = 0;
}

t_img	obj_get_image(t_doom *doom, t_obj *obj)
{
	return (doom->img[obj->images[obj->states_frame][obj->anim_frame]]);
}

int		create_obj_box(t_doom *doom, t_obj *obj)
{
	obj->col_passable = 0;
	obj->col_size = 3.0f;
}

int		create_obj_decor(t_doom *doom, t_obj *obj)
{
	obj->col_passable = 1;
	obj->col_size = 0.1f;
}

int		obj_collision_key_pickup(t_doom *doom, t_obj *obj)
{
	obj->enabled = 0;
	play_sound(doom, SOUND_PICKUP);
	printf("Picked up key with %d id!\n", obj->id);
	doom->player.key = 1;
}

int		obj_collision_weapon_pickup(t_doom *doom, t_obj *obj)
{
	obj->enabled = 0;
	//play_sound(doom, WEAPON_PICKUP);
	printf("Picked up weapon with %d id!\n", obj->id);
	doom->player.allweapons[obj->type - 3] = 1;
}

int		create_obj_key(t_doom *doom, t_obj *obj)
{
	obj->col_passable = 1;
	obj->col_size = 3.0f;
	obj->on_collision = obj_collision_key_pickup;
}

int		create_obj_weapon(t_doom *doom, t_obj *obj)
{
	obj->col_passable = 1;
	obj->col_size = 3.0f;
	obj->on_collision = obj_collision_weapon_pickup;
}

int		create_obj_enemy_default(t_doom *doom, t_obj *obj)
{
	//doom->num.enemy++;
	//enemies should ALWAYS be passable!
	obj->col_passable = 1;
	//col_size is just for not colliding with walls
	obj->col_size = 5.0f;
	create_enemy_default(doom, obj);
}

int		create_obj(t_doom *doom, t_obj *obj)
{
	printf("Creating obj of type %d\n", obj->type);
	if (obj->type == 0)
		create_obj_box(doom, obj);
	else if (obj->type == 1)
		create_obj_key(doom, obj);
	else if (obj->type == 2)
		create_obj_decor(doom, obj);
	else if (obj->type == 3)
		create_obj_enemy_default(doom, obj);
	else if (obj->type == 4 || obj->type == 5 || obj->type == 6)
		create_obj_weapon(doom, obj);
	return (1);
}

int		loadobjs(t_doom *doom, t_obj *obj, t_data *objs_data, char *str)
{
	static int	n = 0;
	float		tmp;
	int			id;
	int			i;
	int			j;
	t_obj		*o;

	o = &doom->objs[n];
	str = todigit(str, &tmp);
	id = (int)tmp;
	str = todigit(str, &o->p.y);
	str = todigit(str, &o->p.x);
	str = todigit(str, &tmp);
	o->id = id;
	o->sector = (int)tmp;
	o->type = objs_data[id].type;
	o->images = objs_data[id].images;
	o->states_count = objs_data[id].states_count;
	o->anim_count = objs_data[id].anim_count;
	o->images = objs_data[id].images;
	o->enabled = 1;
	o->n = n;
	create_obj(doom, o);
	n++;
	return (0);
}