/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sel_txtc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 17:31:38 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/26 17:43:10 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void	sel_txtc(int x, int y, t_all_sect *sects)
{
	if (x >= 950 && x <= 1000 && y >= 310 && y <= 360)
	{
		sects->sectors[sects->selected_sector].txtc == 0 ?
		sects->sectors[sects->selected_sector].txtc = COUNT_T - 1 :
		sects->sectors[sects->selected_sector].txtc--;
	}
	else
	{
		sects->sectors[sects->selected_sector].txtc == COUNT_T - 1 ?
		sects->sectors[sects->selected_sector].txtc = 0 :
		sects->sectors[sects->selected_sector].txtc++;
	}
}