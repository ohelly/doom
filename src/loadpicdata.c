/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadpicdata.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 17:21:12 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/28 23:08:23 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		count_params_pic(char *map, t_data *pic)
{
	float	tmp;
	int		n;
	int		a;
	int		w;
	int		h;

	map = todigit(map, &tmp);
	map = todigit(map, &tmp);
	pic->type = (int)tmp;
	map = todigit(map, &tmp);
	pic->states_count = (int)tmp;
	pic->images = (int**)ft_memalloc(sizeof(int*) * pic->states_count);
	pic->anim_count = (int*)ft_memalloc(sizeof(int) * pic->states_count);
	n = 0;
	while (n < pic->states_count)
	{
		map = todigit(map, &tmp);
		pic->anim_count[n] = (int)tmp;
		pic->images[n] = (int*)ft_memalloc(sizeof(int) * pic->anim_count[n]);
		n++;
	}
	return (0);
}

int		load_pic(char **map, t_data *pic, t_img *img)
{
	int		n;
	int		a;
	int		i;
	int		t;

	i = 0;
	t = 1;
	n = 0;
	count_params_pic(map[i], pic);
	while (n < pic->states_count)
	{
		a = 0;
		while (a < pic->anim_count[n])
		{
			load_image(map[i + t], &pic->images[n][a], img);
			t++;
			a++;
		}
		n++;
	}
	return (0);
}

int		load_pic_data(char **map, t_doom *doom, int i)
{
	int		t;
	int		count;
	float	tmp;

	map[i] = todigit(map[i], &tmp);
	count = (int)tmp;
	doom->pics_data = (t_data*)ft_memalloc(sizeof(t_data) * (count + 1));
	i++;
	while (*map[i] != '#')
	{
		load_pic(&map[i], &doom->pics_data[atoi(map[i])], doom->img);
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
