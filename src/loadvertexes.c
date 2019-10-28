/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadvertexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 11:49:53 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/28 19:59:43 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		loadvertexes(t_xy *v, char *str)
{
	static int	n = 0;
	float		y;

	str = todigit(str, &y);
	while (*str)
	{
		v[n].y = y;
		if (!(str = todigit(str, &v[n].x)))
		{
			break ;
			n++;
		}
		n++;
	}
	return (0);
}
