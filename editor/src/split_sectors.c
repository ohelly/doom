/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_sectors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 17:09:53 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/15 16:07:53 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void		change_sector(t_doom *doom, int v1, int v2, int sec)
{
	int		i;
	int		temp1;
	int		temp2;

	i = -1;
	temp1 = v1;
	temp2 = v2;
	while (++i < doom->walls->count)
	{
		if (temp1 == v2)
			break ;
		if (doom->walls->wall[i].sectors == doom->sects->selected_sector)
		{
			if (doom->walls->wall[i].vert_one == temp1 &&
			doom->walls->wall[i].vert_two != temp2)
			{
				doom->walls->wall[i].sectors = sec;
				temp1 = doom->walls->wall[i].vert_two;
				temp2 = doom->walls->wall[i].vert_one;
				i = -1;
			}
		}
	}
}

void		flip(t_doom *doom, t_swall *swall)
{
	doom->walls->wall[doom->walls->count].vert_one = swall->v1;
	doom->walls->wall[doom->walls->count].vert_two = swall->v2;
	doom->walls->wall[doom->walls->count].portal = -1;
	doom->walls->wall[doom->walls->count++].sectors = swall->sec;
	doom->walls->wall[doom->walls->count].vert_one = swall->v1;
	doom->walls->wall[doom->walls->count].vert_two = swall->v2;
	doom->walls->wall[doom->walls->count].portal = -1;
	doom->walls->wall[doom->walls->count++].sectors = doom->sects->count;
	change_sector(doom, swall->v1, swall->v2, doom->sects->count);
	doom->sects->count++;
}

void		split(t_doom *doom)
{
	if (doom->sects->selected_sector == -1)
	{
		doom->hud->msg = "Select sector";
		doom->swall->sec = -1;
		doom->swall->v1 = -1;
		doom->swall->wall1 = -1;
		return ;
	}
	doom->swall->v2 = vertex_is_free(doom, doom->mouse->ppos);
	if (doom->walls->wall[doom->swall->wall1].vert_two == doom->swall->v2 ||
	doom->swall->v1 == doom->swall->v2 ||
	check_adjacent_wall(doom, doom->swall->v1,
	doom->swall->v2, doom->swall->sec))
	{
		doom->swall->v2 = -1;
		doom->hud->msg = "Select valid vertex";
		return ;
	}
	doom->swall->wall2 = num_walls(doom, doom->swall->v2, doom->swall->sec);
	flip(doom, doom->swall);
	*doom->swall = (t_swall){ -1, -1, -1, -1, -1 };
	doom->sects->selected_sector = -1;
}

void		split_sectors(t_doom *doom)
{
	if (check_portal(doom))
		return ;
	if (doom->swall->v1 == -1)
	{
		if (doom->sects->selected_sector == -1)
		{
			doom->hud->msg = "Select sector!";
			return ;
		}
		doom->swall->sec = doom->sects->selected_sector;
		doom->swall->v1 = vertex_is_free(doom, doom->mouse->ppos);
		doom->swall->wall1 = num_walls(doom, doom->swall->v1, doom->swall->sec);
		if (doom->swall->v1 == -1 || doom->swall->wall1 == -1)
		{
			doom->hud->msg = "Select valid vertex";
			return ;
		}
	}
	else
		split(doom);
}
