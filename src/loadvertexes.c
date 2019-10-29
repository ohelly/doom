/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadvertexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 11:49:53 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/29 04:46:12 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		loadvertexes(t_xy *v, char *str)
{
	static int	n = 0;
	float		y;
	float		tmp;

	str = todigit(str, &y);
	while (*str)
	{
		v[n].y = y / 4.f;
		if (!(str = todigit(str, &tmp)))
		{
			break ;
			n++;
		}
		else
			v[n].x = tmp / 4.f;
		n++;
	}
	return (0);
}
