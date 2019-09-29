/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadpics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 13:47:25 by dtoy              #+#    #+#             */
/*   Updated: 2019/09/27 14:13:17 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		loadpics(t_pic *pic, char *str)
{
	static int	n = 0;
	float	tmp;
	
	str = todigit(str, &pic[n].p.y);
	str = todigit(str, &pic[n].p.x);
	str = todigit(str, &pic[n].z);
	str = todigit(str, &tmp);
	pic[n].wall = (int)tmp;
	str = todigit(str, &tmp);
	pic[n].anim = (int)tmp;
	str = todigit(str, &tmp);
	pic[n].cnt_frms = (int)tmp;
	str = todigit(str, &tmp);
	pic[n].txt_ind = (int)tmp;
	str = todigit(str, &tmp);
	pic[n].sector = (int)tmp;
	return (0);
}