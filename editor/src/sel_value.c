/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sel_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 14:39:25 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/17 15:14:00 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void		sel_floor(int x, int y, t_all_sect *sects)
{
	if (x >= 950 && x <= 1000 && y >= 110 && y <= 160)
	{
		if (sects->sectors[sects->selected_sector].floor > 0)
			sects->sectors[sects->selected_sector].floor--;
	}
	else
	{
		if (sects->sectors[sects->selected_sector].floor < 999 &&
		sects->sectors[sects->selected_sector].floor <
		sects->sectors[sects->selected_sector].ceiling - 16)
			sects->sectors[sects->selected_sector].floor++;
	}
}

void		sel_ceiling(int x, int y, t_all_sect *sects)
{
	if (x >= 950 && x <= 1000 && y >= 60 && y <= 110)
	{
		if (sects->sectors[sects->selected_sector].ceiling > 0 &&
		sects->sectors[sects->selected_sector].ceiling >
		sects->sectors[sects->selected_sector].floor + 16)
			sects->sectors[sects->selected_sector].ceiling--;
	}
	else
	{
		if (sects->sectors[sects->selected_sector].ceiling < 999)
			sects->sectors[sects->selected_sector].ceiling++;
	}
}

void		sel_light(int x, int y, t_all_sect *sects)
{
	if (x >= 950 && x <= 1000 && y >= 510 && y <= 560)
	{
		if (sects->sectors[sects->selected_sector].light > 0)
			sects->sectors[sects->selected_sector].light -= 1;
	}
	else
	{
		if (sects->sectors[sects->selected_sector].light < 100)
			sects->sectors[sects->selected_sector].light += 1;
	}
}
