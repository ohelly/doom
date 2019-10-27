/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadobjdata.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 17:18:55 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/27 17:20:12 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		count_params_obj(char *map, t_data *obj)
{
	float	tmp;
	int		n;
	int		a;
	int		w;
	int		h;

	map = todigit(map, &tmp);
	map = todigit(map, &tmp);
	obj->type = (int)tmp;
	map = todigit(map, &tmp);
	obj->states_count = (int)tmp;
	obj->images = (int**)ft_memalloc(sizeof(int*) * obj->states_count);
	obj->anim_count = (int*)ft_memalloc(sizeof(int) * obj->states_count);
	n = 0;
	while (n < obj->states_count)
	{
		map = todigit(map, &tmp);
		obj->anim_count[n] = (int)tmp;
		obj->images[n] = (int*)ft_memalloc(sizeof(int) * obj->anim_count[n]);
		n++;
	}
	return (0);
}

int		load_obj(char **map, t_data *obj, t_img *img)
{
	int		n;
	int		a;
	int		i;
	int		t;

	i = 0;
	t = 1;
	n = 0;
	count_params_obj(map[i], obj);
	while (n < obj->states_count)
	{
		a = 0;
		while (a < obj->anim_count[n])
		{
			load_image(map[i + t], &obj->images[n][a], img);
			t++;
			a++;
		}
		n++;
	}
	return (0);
}

int		load_obj_data(char **map, t_doom *doom)
{
	int		i;
	int		t;
	int		count;
	float	tmp;

	map[0] = todigit(map[0], &tmp);
	count = (int)tmp;
	doom->objs_data = (t_data*)ft_memalloc(sizeof(t_data) * (count + 1));
	i = 1;
	while (*map[i] != '#')
	{
		load_obj(&map[i], &doom->objs_data[atoi(map[i])], doom->img);
		while (*map[i] != '.')
		{
			if (*map[i] == '#')
				return (0);
			i++;
		}
		i++;
	}
	return (0);
}
