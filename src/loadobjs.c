/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadobjs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 12:50:34 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/13 12:27:21 by dtoy             ###   ########.fr       */
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

/*
t_img	obj_get_image(t_doom *doom, t_obj *obj)
{
	return (doom->images[obj->images[obj->states_frame][obj->anim_frame]]);
}
*/
int		loadobjs(t_obj *obj, t_data *objs_data, char *str)
{
	static int	n = 0;
	float		tmp;
	int			id;
	int			i;
	int			j;

	str = todigit(str, &tmp);
	id = (int)tmp;
	str = todigit(str, &obj[n].p.y);
	str = todigit(str, &obj[n].p.x);
	str = todigit(str, &tmp);
	obj[n].sector = (int)tmp;
	obj[n].type = objs_data[id].type;
	obj[n].images = objs_data[id].images;
	obj[n].anim_count = objs_data[id].anim_count;
	obj[n].states_count = objs_data[id].states_count;
	//str = todigit(str, &tmp);
	//obj[n].images = (int**)malloc(sizeof(int*) * ((int)tmp + 1));
	//obj[n].states_count = (int)tmp;

	//i = tmp;
	//str = todigit(str, &tmp);
	//obj[n].anim_count = (int)tmp;
	//while (i >= 0)
	//{
	//	obj[n].images[i] = (int*)malloc(sizeof(int) * ((int)tmp + 1));
	//	j = 0;
	//	while (j < tmp)
	//	{
	//		obj[n].images[i][j] = -1;
	//		j++;
	//	}
	//	i--;
	//}
	n++;
	return (0);
}