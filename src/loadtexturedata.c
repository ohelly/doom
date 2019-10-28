/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadtexturedata.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 16:57:47 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/28 23:08:02 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			load_texture_data2(char **map, t_texture *txt, t_img *img, int c)
{
	float	tmp;
	int		i;
	int		a;
	int		w;
	int		h;

	a = 0;
	i = 1;
	while (i <= c)
	{
		map[i] = todigit(map[i], &tmp);
		w = (int)tmp;
		map[i] = todigit(map[i], &tmp);
		h = (int)tmp;
		txt[a].image = new_image(map[i], img, w, h);
		a++;
		i++;
	}
	return (0);
}

t_texture	*load_texture(char **map, t_texture *txt, t_img *img)
{
	int		count;
	float	tmp;

	map[0] = todigit(map[0], &tmp);
	count = (int)tmp;
	if (!(txt = (t_texture*)ft_memalloc(sizeof(t_texture) * count)))
		return (NULL);
	load_texture_data2(map, txt, img, count);
	return (txt);
}

int			load_texture_data(char **map, t_doom *doom, int i)
{
	while (*map[i] != '#')
	{
		if (*map[i] == 'S')
			doom->sky = load_texture(&map[i], doom->sky, doom->img);
		if (*map[i] == 'W')
			doom->walls = load_texture(&map[i], doom->walls, doom->img);
		if (*map[i] == 'C')
			doom->ceils = load_texture(&map[i], doom->ceils, doom->img);
		if (*map[i] == 'F')
			doom->floors = load_texture(&map[i], doom->floors, doom->img);
		if (*map[i] == 'B')
			doom->bullet = load_texture(&map[i], doom->bullet, doom->img);
		i++;
	}
	return (0);
}
