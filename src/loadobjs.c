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

int		loadobjs(t_obj *obj, char *str)
{
	static int	n = 0;
	float		tmp;

	str = todigit(str, &obj[n].p.y);
	str = todigit(str, &obj[n].p.x);
	str = todigit(str, &tmp);
	obj[n].anim = (int)tmp;
	str = todigit(str, &tmp);
	obj[n].cnt_frms = (int)tmp;
	str = todigit(str, &tmp);
	obj[n].rotate = (int)tmp;
	str = todigit(str, &obj[n].pov);
	str = todigit(str, &tmp);
	obj[n].txt_ind = 0;
	str = todigit(str, &tmp);
	obj[n].sector = (int)tmp;
	n++;
	return (0);
}