/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sel_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 19:49:16 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/17 15:01:51 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void	sel_wall(int x, int y, t_all_sect *sects, t_all_walls *walls)
{
	if (x >= 950 && x <= 1000 && y >= 560 && y <= 610)
	{
		if (sects->selected_sector != -1 ||
		walls->selected_wall == -1)
		{
			sv(&walls->selected_wall, &sects->selected_sector);
			return ;
		}
		walls->selected_wall == 0 ? walls->selected_wall =
		walls->count - 1 : walls->selected_wall--;
	}
	else
	{
		if (sects->selected_sector != -1 ||
		walls->selected_wall == -1)
		{
			sv(&walls->selected_wall, &sects->selected_sector);
			return ;
		}
		walls->selected_wall == walls->count - 1 ?
		walls->selected_wall = 0 : walls->selected_wall++;
	}
}
