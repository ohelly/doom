/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 12:15:54 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/29 01:49:03 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

char		*todigit(char *str, float *data)
{
	int		j;

	j = 0;
	while (str[j] && !(ft_isdigit(str[j])) && str[j] != '.' && str[j] != '-')
		j++;
	*data = atof(&str[j]);
	while (str[j] && (ft_isdigit(str[j]) || str[j] == '.' || str[j] == '-'))
		j++;
	return (&str[j]);
}

float		vxs(float x0, float y0, float x1, float y1)
{
	return (x0 * y1 - x1 * y0);
}

float		yaw(float y, float z, t_player player)
{
	return (y + z * player.yaw);
}

int			intersect_box(t_xy p, t_xy d, t_xy v1, t_xy v2)
{
	return (overlap(p.x, d.x, v1.x, v2.x) && overlap(p.y, d.y, v1.y, v2.y));
}

int			point_side(t_xy d, t_xy v1, t_xy v2)
{
	return (vxs(v2.x - v1.x, v2.y - v1.y, d.x - v1.x, d.y - v1.y));
}
