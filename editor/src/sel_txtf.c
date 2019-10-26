/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sel_txtf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 17:46:04 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/26 17:48:03 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void	sel_txtf(int x, int y, t_all_sect *sects)
{
	if (x >= 950 && x <= 1000 && y >= 210 && y <= 260)
	{
		sects->sectors[sects->selected_sector].txtf == 0 ?
		sects->sectors[sects->selected_sector].txtf = COUNT_T - 1 :
		sects->sectors[sects->selected_sector].txtf--;
	}
	else
	{
		sects->sectors[sects->selected_sector].txtf == COUNT_T - 1 ?
		sects->sectors[sects->selected_sector].txtf = 0 :
		sects->sectors[sects->selected_sector].txtf++;
	}
}