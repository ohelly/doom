/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadobjs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 12:50:34 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/17 13:19:33 by dtoy             ###   ########.fr       */
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
	printf("Trying to get img for %d obj of %d state and %d anim\n", obj->id, obj->states_frame, obj->anim_frame);
	printf("Image exists with index %d\n", obj->images[obj->states_frame][obj->anim_frame]);
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
}

int		create_obj_key(t_doom *doom, t_obj *obj)
{
	obj->col_passable = 1;
	obj->col_size = 3.0f;
	obj->on_collision = obj_collision_key_pickup;
}

int		create_obj_enemy_default(t_doom *doom, t_obj *obj)
{
	//enemies should ALWAYS be passable!
	obj->col_passable = 1;
	obj->col_size = 2.0f;
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
	//printf("We are reading id, curr string is: %s\n", str);
	str = todigit(str, &tmp);
	id = (int)tmp;
	//printf("Id is %d, rest of the string is: %s\n", id, str);
	str = todigit(str, &o->p.y);
	str = todigit(str, &o->p.x);
	str = todigit(str, &tmp);
	o->id = id;
	o->sector = (int)tmp;
	o->type = objs_data[id].type;
	o->images = objs_data[id].images;
	o->anim_count = (int*)malloc(sizeof(int) * o->states_count);
	o->states_count = objs_data[id].states_count;
	printf("Allocating %d for states\n", o->states_count);
	o->images = (int**)malloc(sizeof(int*) * o->states_count + 1);

	i = 0;
	while (i < o->states_count)
	{
		o->anim_count[i] = objs_data[id].anim_count[i];
		printf("Allocating %d for anim %d\n", o->anim_count[i], i);
		o->images[i] = (int*)malloc(sizeof(int) * o->anim_count[i] + 1);
		j = 0;
		while (j < o->anim_count[i])
		{
			o->images[i][j] = objs_data[id].images[i][j];
			printf("Added image %d in %d:%d to obj with id %d, n is %d\n", o->images[i][j], i, j, id, n);
			j++;
		}
		i++;
	}
	printf("Vibe check %d\n", o->images[0][0]);
	printf("We added %d\n", o->images[3][0]);
	printf("Does it exist? %d\n", doom->objs[n].images[3][0]);
	o->enabled = 1;
	create_obj(doom, o);
	n++;
	return (0);
}