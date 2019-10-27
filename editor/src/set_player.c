/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 14:29:45 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/27 15:27:51 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void		set_weapon(int x, int y, t_player *player)
{
	if (x >= 950 && x <= 1000 && y >= 360 && y <= 410)
	{
		player->weapon == 0 ?
		player->weapon = COUNT_WP - 1 :
		player->weapon--;
	}
	else
	{
		player->weapon == COUNT_WP - 1 ?
		player->weapon = 0 :
		player->weapon++;
	}
}

void		set_end_player(t_doom *doom)
{
	if (doom->sects->selected_sector == -1)
	{
		doom->hud->msg = "Select sector";
		return ;
	}
	if (doom->player->sec == -1)
	{
		doom->hud->msg = "Set start position";
		return ;
	}
	if (doom->sects->selected_sector == doom->player->sec)
	{
		doom->hud->msg = "Select valid sector";
		return ;
	}
	doom->player->end = doom->sects->selected_sector; 
}

void		draw_player(t_doom *doom, int color)
{
	if (doom->player->pos.x != -1 && doom->player->pos.y != -1)
		draw_rectangle(doom, doom->player->pos, color, 5);
}

void		set_player(t_doom *doom)
{
	if (doom->sects->selected_sector == -1)
	{
		doom->hud->msg = "Select sector";
		return ;
	}
	doom->player->sec = doom->sects->selected_sector;
	doom->player->pos.x = doom->mouse->ppos.x;
	doom->player->pos.y = doom->mouse->ppos.y;
}
