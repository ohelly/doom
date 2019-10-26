/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sel_sector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 19:44:21 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/17 15:01:35 by ohelly           ###   ########.fr       */
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
	else
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
