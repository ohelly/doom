/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadimage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 17:24:22 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/27 17:25:31 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		new_image(char *str, t_img *img, int w, int h)
{
	static int	ind = 0;
	float		tmp;
	int			j;

	j = 0;
	img[ind].data = (int*)ft_memalloc(sizeof(int) * w * h);
	img[ind].w = w;
	img[ind].h = h;
	while (j < w * h)
	{
		str = todigit(str, &tmp);
		img[ind].data[j] = (int)tmp;
		j++;
	}
	return (ind++);
}

int		load_image(char *map, int *image, t_img *img)
{
	int		w;
	int		h;
	float	tmp;

	map = todigit(map, &tmp);
	w = (int)tmp;
	map = todigit(map, &tmp);
	h = (int)tmp;
	*image = new_image(map, img, w, h);
	return (0);
}
