/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sel_attr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 19:55:47 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/16 19:58:30 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void	sel_attr(int x, int y, t_all_sect *sects, t_all_walls *walls)
{
	if (x >= 1200 && x <= 1250 && y >= 360 && y <= 410)
	{
		if (doom->sects->sectors[doom->sects->selected_sector].skyb == 0)
			doom->sects->sectors[doom->sects->selected_sector].skyb = 1;
		else
			doom->sects->sectors[doom->sects->selected_sector].skyb = 0;
	}
	else if (x >= 1200 && x <= 1250 && y >= 460 && y <= 510)
	{
		if (doom->walls->wall[doom->walls->selected_wall].portal == -1)
			doom->walls->wall[doom->walls->selected_wall].portal = -2;
		else
			doom->walls->wall[doom->walls->selected_wall].portal = -1;
	}
	else if (x >= 1200 && x <= 1250 && y >= 410 && y <= 460)
	{
		if (doom->sects->sectors[doom->sects->selected_sector].door == 0)
			doom->sects->sectors[doom->sects->selected_sector].door = 1;
		else
			doom->sects->sectors[doom->sects->selected_sector].door = 0;
	}
}
