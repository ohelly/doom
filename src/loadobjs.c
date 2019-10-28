/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadobjs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 12:50:34 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/28 20:54:48 by glormell         ###   ########.fr       */
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

	if (obj->enabled == 0)
		return ;
	state = obj->states_frame;
	if (obj->anim_count[state] <= 1)
		return ;
	obj->anim_frame++;
	if (obj->anim_frame >= obj->anim_count[state] ||
	obj->images[state][obj->anim_frame] == -1)
	{
		obj->anim_frame = 0;
		if (obj->on_anim_end != NULL)
			obj->on_anim_end(obj);
	}
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

int		create_obj_explosive(t_doom *doom, t_obj *obj)
{
	obj->col_passable = 0;
	obj->col_size = 3.0f;
	obj->on_hit = obj_hit_explosive;
}

void	obj_hit_breakable(t_doom *doom, t_obj *obj)
{
	obj_state_change(obj, 1);
}

int		create_obj_breakable(t_doom *doom, t_obj *obj)
{
	obj->col_passable = 0;
	obj->col_size = 3.0f;
	obj->on_hit = obj_hit_breakable;
}

int		create_obj_enemy_default(t_doom *doom, t_obj *obj)
{
	obj->col_passable = 1;
	obj->col_size = 5.0f;
	obj->scale = 6.0f;
	create_enemy_default(doom, obj);
}

int		create_obj(t_doom *doom, t_obj *obj)
{
	if (obj->type == OBJ_TYPE_BOX)
		create_obj_box(doom, obj);
	else if (obj->type == OBJ_TYPE_BREAKABLE)
		create_obj_breakable(doom, obj);
	else if (obj->type == OBJ_TYPE_EXPLOSIVE)
		create_obj_explosive(doom, obj);
	else if (obj->type == OBJ_TYPE_ENEMY_REG)
		create_obj_enemy_default(doom, obj);
	else if (obj->type == OBJ_TYPE_PISTOL ||
	obj->type == OBJ_TYPE_SHOTGUN || obj->type == OBJ_TYPE_SMG)
		create_obj_weapon(doom, obj);
	else if (obj->type == OBJ_TYPE_AMMO_P ||
	obj->type == OBJ_TYPE_AMMO_SH || obj->type == OBJ_TYPE_AMMO_SMG)
		create_obj_ammo(doom, obj);
	else if (obj->type == OBJ_TYPE_MED_SMALL ||
	obj->type == OBJ_TYPE_MED_MEDIUM || obj->type == OBJ_TYPE_MED_BIG)
		create_obj_medkit(doom, obj);
	else if (obj->type == OBJ_TYPE_KEY)
		create_obj_key(doom, obj);
	return (1);
}

int		loadobjs(t_doom *doom, char *str)
{
	static int	n = 0;
	float		tmp;
	t_obj		*o;

	o = &doom->objs[n];
	str = todigit(str, &tmp);
	o->id = (int)tmp;
	str = todigit(str, &o->p.y);
	str = todigit(str, &o->p.x);
	str = todigit(str, &tmp);
	o->sector = (int)tmp;
	o->type = doom->objs_data[o->id].type;
	o->images = doom->objs_data[o->id].images;
	o->states_count = doom->objs_data[o->id].states_count;
	o->anim_count = doom->objs_data[o->id].anim_count;
	o->images = doom->objs_data[o->id].images;
	o->enabled = 1;
	o->n = n;
	o->scale = 4.0f;
	if (o->type == OBJ_TYPE_KEY)
		doom->hud->key = o;
	create_obj(doom, o);
	n++;
	return (0);
}
