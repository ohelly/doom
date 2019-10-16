/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sel_sector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 19:44:21 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/16 19:45:46 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void	sel_sector(int x, int y, t_all_sect *sects, t_all_walls *walls)
{
	if (x >= 950 && x <= 1000 && y >= 10 && y <= 60 && sects->count > 1)
	{
		if (sects->selected_sector == -1 ||
		walls->selected_wall != -1)
		{
			sv(&sects->selected_sector, &walls->selected_wall);
			return ;
		}
		sects->selected_sector == 0 ? sects->selected_sector =
		sects->count - 1 : sects->selected_sector--;
	}
	else if (x > 1199 && x < 1251 && y > 9 && y < 61 && sects->count > 1)
	{
		if (sects->selected_sector == -1 ||
		walls->selected_wall != -1)
		{
			sv(&sects->selected_sector, &walls->selected_wall);
			return ;
		}
		sects->selected_sector == sects->count - 1 ?
		sects->selected_sector = 0 : sects->selected_sector++;
	}
}
