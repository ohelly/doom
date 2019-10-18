/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_skybox.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 15:19:05 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/17 15:24:06 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void		change_skybox(int x, int y, t_txt *txt)
{
	if (x >= 650 && x <= 710 && y >= 10 && y <= 60)
		txt->ind_sky == 0 ? txt->ind_sky = COUNT_SKY - 1 : txt->ind_sky--;
	else
		txt->ind_sky == COUNT_SKY - 1 ? txt->ind_sky = 0 : txt->ind_sky++;
}
