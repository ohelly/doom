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

void	obj_anim_next(t_obj *obj, int state)
{
	int index;

	obj->anim_frame++;
	if (obj->anim_frame >= obj->anim_count[state] || obj->images[state][obj->anim_frame] == -1)
		obj->anim_frame = 0;
}


t_img  	obj_get_image(t_doom *doom, t_obj *obj)
{
	return (doom->img[obj->images[obj->states_frame][obj->anim_frame]]);
}
int		create_obj(t_doom *doom, t_obj *obj)
{
	if (obj->type == 0)
		return (1);
		//create_obj_box(doom, obj);
	else if (obj->type == 1)
		return (1);
		//create_obj_key(doom, obj);
	else if (obj->type == 2)
		return (1);
		//create_obj_enemy_small(doom, obj);
	return (0);
}

int		loadobjs(t_doom *doom, t_obj *obj, t_data *objs_data, char *str)
{
	static int	n = 0;
	float		tmp;
	int			id;
	int			i;
	int			j;

	//printf("We are reading id, curr string is: %s\n", str);
	str = todigit(str, &tmp);
	id = (int)tmp;
	//printf("Id is %d, rest of the string is: %s\n", id, str);
	str = todigit(str, &obj[n].p.y);
	str = todigit(str, &obj[n].p.x);
	str = todigit(str, &tmp);
	obj[n].sector = (int)tmp;
	obj[n].type = objs_data[id].type;
	obj[n].images = objs_data[id].images;
	obj[n].anim_count = objs_data[id].anim_count;
	obj[n].states_count = objs_data[id].states_count;

	obj[n].images = (int**)malloc(sizeof(int*) * obj[n].states_count);
	i = 0;
	while (i < obj[n].states_count)
	{
		obj[n].images[i] = (int*)malloc(sizeof(int) * obj[n].anim_count[i]);
		j = 0;
		while (j < obj[n].anim_count[i])
		{
			obj[n].images[i][j] = objs_data[id].images[i][j];
			printf("Added image %d to obj with id %d, n is %d\n", obj[n].images[i][j], id, n);
			j++;
		}
		i++;
	}
	create_obj(doom, obj);
	n++;
	return (0);
}