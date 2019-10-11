/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_press.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 15:16:30 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/11 14:59:05 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void		mouse_press_right(t_doom *doom, int x, int y)
{
	if (x >= 950 && x <= 1000 && y >= 60 && y <= 110)
	{
		if (doom->sects->sectors[doom->sects->selected_sector].floor >= 10)
			doom->sects->sectors[doom->sects->selected_sector].floor -= 10;
	}
	else if (x >= 1200 && x <= 1250 && y >= 60 && y <= 110)
	{
		if (doom->sects->sectors[doom->sects->selected_sector].floor <= 989)
			doom->sects->sectors[doom->sects->selected_sector].floor += 10;
	}
	else if (x >= 950 && x <= 1000 && y >= 110 && y <= 160)
	{
		if (doom->sects->sectors[doom->sects->selected_sector].ceiling >= 10)
			doom->sects->sectors[doom->sects->selected_sector].ceiling -= 10;
	}
	else if (x >= 1200 && x <= 1250 && y >= 110 && y <= 160)
	{
		if (doom->sects->sectors[doom->sects->selected_sector].ceiling <= 989)
			doom->sects->sectors[doom->sects->selected_sector].ceiling += 10;
	}
	else if (x >= 950 && x <= 1000 && y >= 510 && y <= 560)
	{
		if (doom->sects->sectors[doom->sects->selected_sector].light >= 10)
			doom->sects->sectors[doom->sects->selected_sector].light -= 10;
	}
	else if (x >= 1200 && x <= 1250 && y >= 510 && y <= 560)
	{
		if (doom->sects->sectors[doom->sects->selected_sector].light <= 90)
			doom->sects->sectors[doom->sects->selected_sector].light += 10;
	}
}

void		mouse_press_left(t_doom *doom, int x, int y)
{
	if (x >= 950 && x <= 1000 && y >= 10 && y <= 60)
	{
		if (doom->sects->selected_sector == -1 || doom->walls->selected_wall != -1)
		{
			doom->sects->selected_sector = 0;
			doom->walls->selected_wall = -1;
			return ;
		}
		if (doom->sects->count < 2)
			return ;
		if (doom->sects->selected_sector == 0)
			doom->sects->selected_sector = doom->sects->count;
		doom->sects->selected_sector--;
	}
	else if (x >= 1200 && x <= 1250 && y >= 10 && y <= 60)
	{
		if (doom->sects->selected_sector == -1 || doom->walls->selected_wall != -1)
		{
			doom->sects->selected_sector = 0;
			doom->walls->selected_wall = -1;
			return ;
		}
		if (doom->sects->count < 2)
			return ;
		if (doom->sects->selected_sector == doom->sects->count - 1)
			doom->sects->selected_sector = -1;
		doom->sects->selected_sector++;
	}
	else if (x >= 950 && x <= 1000 && y >= 60 && y <= 110)
	{
		if (doom->sects->sectors[doom->sects->selected_sector].floor > 0)
			doom->sects->sectors[doom->sects->selected_sector].floor--;
	}
	else if (x >= 1200 && x <= 1250 && y >= 60 && y <= 110)
	{
		if (doom->sects->sectors[doom->sects->selected_sector].floor < 999)
			doom->sects->sectors[doom->sects->selected_sector].floor++;
	}
	else if (x >= 950 && x <= 1000 && y >= 110 && y <= 160)
	{
		if (doom->sects->sectors[doom->sects->selected_sector].ceiling > 0)
			doom->sects->sectors[doom->sects->selected_sector].ceiling--;
	}
	else if (x >= 1200 && x <= 1250 && y >= 110 && y <= 160)
	{
		if (doom->sects->sectors[doom->sects->selected_sector].ceiling < 999)
			doom->sects->sectors[doom->sects->selected_sector].ceiling++;
	}
	else if (x >= 1200 && x <= 1250 && y >= 360 && y <= 410)
	{
		if (doom->sects->sectors[doom->sects->selected_sector].skyb == 0)
			doom->sects->sectors[doom->sects->selected_sector].skyb = 1;
		else
			doom->sects->sectors[doom->sects->selected_sector].skyb = 0;
	}
	else if (x >= 1200 && x <= 1250 && y >= 410 && y <= 460)
	{
		if (doom->sects->sectors[doom->sects->selected_sector].door == 0)
			doom->sects->sectors[doom->sects->selected_sector].door = 1;
		else
			doom->sects->sectors[doom->sects->selected_sector].door = 0;
	}
	else if (x >= 1200 && x <= 1250 && y >= 460 && y <= 510)
	{
		if (doom->walls->wall[doom->walls->selected_wall].portal == -1)
			doom->walls->wall[doom->walls->selected_wall].portal = -2;
		else
			doom->walls->wall[doom->walls->selected_wall].portal = -1;
	}
	else if (x >= 950 && x <= 1000 && y >= 560 && y <= 610)
	{
		if (doom->sects->selected_sector != -1 || doom->walls->selected_wall == -1)
		{
			doom->sects->selected_sector = -1;
			doom->walls->selected_wall = 0;
			return ;
		}
		if (doom->walls->selected_wall == 0)
			doom->walls->selected_wall = doom->walls->count;
		doom->walls->selected_wall--;
	}
	else if (x >= 1200 && x <= 1250 && y >= 560 && y <= 610)
	{
		if (doom->sects->selected_sector != -1 || doom->walls->selected_wall == -1)
		{
			doom->sects->selected_sector = -1;
			doom->walls->selected_wall = 0;
			return ;
		}
		if (doom->walls->selected_wall == doom->walls->count - 1)
			doom->walls->selected_wall = -1;
		doom->walls->selected_wall++;
	}
	else if (x >= 950 && x <= 1000 && y >= 660 && y <= 710)
	{
		if (doom->walls->wall[doom->walls->selected_wall].txt == 0)
			doom->walls->wall[doom->walls->selected_wall].txt = COUNT_W;
		doom->walls->wall[doom->walls->selected_wall].txt--;
	}
	else if (x >= 1200 && x <= 1250 && y >= 660 && y <= 710)
	{
		if (doom->walls->wall[doom->walls->selected_wall].txt == COUNT_W - 1)
			doom->walls->wall[doom->walls->selected_wall].txt = -1;
		doom->walls->wall[doom->walls->selected_wall].txt++;
	}
	else if (x >= 950 && x <= 1000 && y >= 510 && y <= 560)
	{
		if (doom->sects->sectors[doom->sects->selected_sector].light > 0)
			doom->sects->sectors[doom->sects->selected_sector].light -= 1;
	}
	else if (x >= 1200 && x <= 1250 && y >= 510 && y <= 560)
	{
		if (doom->sects->sectors[doom->sects->selected_sector].light < 100)
			doom->sects->sectors[doom->sects->selected_sector].light += 1;
	}
	else if (x >= 650 && x <= 710 && y >= 10 && y <= 60)
		printf("kek\n");
	else if (x >= 900 && x <= 950 && y >= 10 && y <= 60)
		printf("eke\n");
}