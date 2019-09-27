/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_vertices.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:33:32 by dtoy              #+#    #+#             */
/*   Updated: 2019/09/19 15:19:48 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		loadvertices(t_doom *doom, t_xy *v, char *str)
{
	static int	n = 0;
	int			j;
	int			t;
	float		y;

	j = 0;
	t = 0;
	while (j < ft_strlen(str))
	{
		if (ft_isdigit(str[j]) && t == 0)
		{
			t = 1;
			y = atof(&str[j]);
			while (ft_isdigit(str[j]) || str[j] == '.')
				j++;
		}
		else if (ft_isdigit(str[j]) && t == 1)
		{
			v[n].y = y;
			v[n].x = atof(&str[j]);
			while (ft_isdigit(str[j]) || str[j] == '.')
				j++;
			n++;
		}
		else
			j++;
	}
	return (0);
}