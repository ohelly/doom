/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadpics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 13:47:25 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/11 18:27:01 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		loadpics(t_pics *pic, char *str)
{
	static int	n = 0;
	float	tmp;
	
	str = todigit(str, &pic[n].p.y);
	str = todigit(str, &pic[n].p.x);
	str = todigit(str, &pic[n].p.z);
	//printf("pic y - %f, pic x - %f, pic z - %f\n", pic[n].p.y, pic[n].p.x, pic[n].p.z);
	str = todigit(str, &tmp);
	pic[n].wall = (int)tmp;
	//printf("wall - %d\n", pic[n].wall);
	str = todigit(str, &tmp);
	pic[n].sector = (int)tmp;
	//printf("sector - %d\n", pic[n].sector);
	n++;
	return (0);
}