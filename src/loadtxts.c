/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadtxts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 14:14:19 by dtoy              #+#    #+#             */
/*   Updated: 2019/09/27 14:16:30 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		loadtxts(t_texture *txt, char *str)
{
	static int	n = 0;
	float		tmp;

	str = todigit(str, &tmp);
	txt[n].sector = (int)tmp;
	str = todigit(str, &tmp);
	txt[n].wall = (int)tmp;
	str = todigit(str, &tmp);
	txt[n].txt_ind = (int)tmp;
	return (0);
}