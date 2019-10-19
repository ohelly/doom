/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sel_attr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 19:55:47 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/17 15:13:11 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void	sel_attr(int x, int y, t_all_sect *sects, t_all_walls *walls)
{
	if (x >= 1200 && x <= 1250 && y >= 360 && y <= 410)
	{
		if (sects->sectors[sects->selected_sector].skyb == 0)
			sects->sectors[sects->selected_sector].skyb = 1;
		else
			sects->sectors[sects->selected_sector].skyb = 0;
	}
	else if (x >= 1200 && x <= 1250 && y >= 460 && y <= 510)
	{
		if (walls->wall[walls->selected_wall].portal == -1)
			walls->wall[walls->selected_wall].portal = -2;
		else
			walls->wall[walls->selected_wall].portal = -1;
	}
	else
	{
		if (sects->sectors[sects->selected_sector].door == 0)
			sects->sectors[sects->selected_sector].door = 1;
		else
			sects->sectors[sects->selected_sector].door = 0;
	}
}
