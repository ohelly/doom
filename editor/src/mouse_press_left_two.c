/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_press_left_two.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:46:49 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/16 19:59:55 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void		mouse_press_left_two_p_5(t_doom *doom, int x, int y)
{
	if (x >= 950 && x <= 1000 && y >= 510 && y <= 560)
	{
		if (doom->sects->sectors[doom->sects->selected_sector].light > 0)
			doom->sects->sectors[doom->sects->selected_sector].light -= 1;
	}
	else if (x >= 1200 && x <= 1250 && y >= 510 && y <= 560)
	{
		if (doom->sects->sectors[doom->sects->selected_sector].light < 100)
			doom->sects->sectors[doom->sects->selected_sector].light += 1;
	}
	else if (x >= 1200 && x <= 1250 && y >= 660 && y <= 710)
	{
		if (doom->walls->wall[doom->walls->selected_wall].txt == COUNT_T - 1)
			doom->walls->wall[doom->walls->selected_wall].txt = -1;
		doom->walls->wall[doom->walls->selected_wall].txt++;
	}
}

void		mouse_press_left_two_p_4(t_doom *doom, int x, int y)
{
	if (x >= 950 && x <= 1000 && y >= 660 && y <= 710)
	{
		if (doom->walls->wall[doom->walls->selected_wall].txt == 0)
			doom->walls->wall[doom->walls->selected_wall].txt = COUNT_T;
		doom->walls->wall[doom->walls->selected_wall].txt--;
	}
	else if (x >= 650 && x <= 710 && y >= 10 && y <= 60)
		printf("kek\n");
	else if (x >= 900 && x <= 950 && y >= 10 && y <= 60)
		printf("eke\n");
	else
		mouse_press_left_two_p_5(doom, x, y);
}

void		mouse_press_left_two_p_3(t_doom *doom, int x, int y)
{
	if (x >= 950 && x <= 1000 && y >= 60 && y <= 110)
	{
		if (doom->sects->sectors[doom->sects->selected_sector].ceiling > 0)
			doom->sects->sectors[doom->sects->selected_sector].ceiling--;
	}
	else if (x >= 1200 && x <= 1250 && y >= 60 && y <= 110)
	{
		if (doom->sects->sectors[doom->sects->selected_sector].ceiling < 999)
			doom->sects->sectors[doom->sects->selected_sector].ceiling++;
	}
	else if (x >= 950 && x <= 1000 && y >= 110 && y <= 160)
	{
		if (doom->sects->sectors[doom->sects->selected_sector].floor > 0)
			doom->sects->sectors[doom->sects->selected_sector].floor--;
	}
	else if (x >= 1200 && x <= 1250 && y >= 110 && y <= 160)
	{
		if (doom->sects->sectors[doom->sects->selected_sector].floor < 999)
			doom->sects->sectors[doom->sects->selected_sector].floor++;
	}
	else
		mouse_press_left_two_p_4(doom, x, y);
}

void		mouse_press_left_two(t_doom *doom, int x, int y)
{
	if ((x >= 950 && x <= 1000 && y >= 10 && y <= 60 && doom->sects->count > 1)
	|| (x > 1199 && x < 1251 && y > 9 && y < 61 && doom->sects->count > 1))
		sel_sector(x, y, doom->sects, doom->walls);
	else if ((x >= 950 && x <= 1000 && y >= 560 && y <= 610) ||
	(x >= 1200 && x <= 1250 && y >= 560 && y <= 610))
		sel_wall(x, y, doom->sects, doom->walls);
	else if ((x >= 1200 && x <= 1250 && y >= 360 && y <= 410) ||
	(x >= 1200 && x <= 1250 && y >= 460 && y <= 510) ||
	(x >= 1200 && x <= 1250 && y >= 410 && y <= 460))
		sel_attr(x, y, doom->sects, doom->walls);
	else
		mouse_press_left_two_p_3(doom, x, y);
}
