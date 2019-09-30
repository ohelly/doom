/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadobjs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 12:50:34 by dtoy              #+#    #+#             */
/*   Updated: 2019/09/29 19:05:13 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	obj_state_change(t_obj *obj, int state)
{
	if (state >= obj->states_count)
		return ;
	obj->states_frame = state;
}

void	obj_anim_next(t_obj *obj)
{
	obj->anim_frame++;
	if (obj->anim_frame >= obj->anim_count)
		obj->anim_frame = 0;
}

t_img	obj_get_image(t_doom *doom, t_obj *obj)
{
	return (doom->images[obj->images[obj->states_frame][obj->anim_frame]]);
}

int		loadobjs(t_obj *obj, char *str)
{
	static int	n = 0;
	float		tmp;
	int			i;

	str = todigit(str, &obj[n].p.y);
	str = todigit(str, &obj[n].p.x);

	str = todigit(str, &tmp);
	obj[n].images = (int**)malloc(sizeof(int*) * ((int)tmp + 1));

	i = tmp;
	while (i >= 0)
	{
		str = todigit(str, &tmp);
		obj[n].images[i] = (int*)malloc(sizeof(int) * ((int)tmp + 1));
		i--;
	}

	str = todigit(str, &tmp);
	obj[n].sector = (int)tmp;

	obj[n].state_change = obj_state_change;
	obj[n].anim_next = obj_anim_next;
	obj[n].get_img = obj_get_image;
	printf("Loaded %d obj\n", n);
	printf("obj states %d, anims %d.\n", obj[n].states_count, obj[n].anim_count);

	n++;
	return (0);
}