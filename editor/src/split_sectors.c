/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_sectors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 17:09:53 by ohelly            #+#    #+#             */
/*   Updated: 2019/09/29 19:43:11 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

int			num_walls(t_doom *doom, int ver, int sec)
{
	int		i;

	i = -1;
	while (++i < doom->walls->count)
		if (doom->walls->wall[i].sectors == sec)
			if (doom->walls->wall[i].vert_one == ver)
				return (i);
	return (-1);
}

int			check_adjacent_wall(t_doom *doom, int ver1, int ver2, int sec)
{
	int		i;

	i = -1;
	while (++i < doom->walls->count)
		if (doom->walls->wall[i].sectors == sec)
			if (doom->walls->wall[i].vert_two == ver1 && doom->walls->wall[i].vert_one == ver2)
				return (1);
	return (0);
}

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
			if (doom->walls->wall[i].vert_one == temp1 && doom->walls->wall[i].vert_two != temp2)
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

void		split_sectors(t_doom *doom)
{
	if (doom->swall->v1 == -1)
	{
		if (doom->sects->selected_sector == -1)
		{
			ft_putendl("Select sector!");
			return ;
		}
		doom->swall->sec = doom->sects->selected_sector;
		doom->swall->v1 = vertex_is_free(doom, doom->mouse->ppos);
		doom->swall->wall1 = num_walls(doom, doom->swall->v1, doom->swall->sec);
		if (doom->swall->v1 == -1 || doom->swall->wall1 == -1)
		{
			ft_putendl("Select valid vertex");
			return ;
		}
	}
	else
	{
		if (doom->sects->selected_sector == -1)
		{
			ft_putendl("Select sector");
			doom->swall->sec = -1;
			doom->swall->v1 = -1;
			doom->swall->wall1 = -1;
			return ;
		}
		doom->swall->v2 = vertex_is_free(doom, doom->mouse->ppos);
		if (doom->walls->wall[doom->swall->wall1].vert_two == doom->swall->v2 ||
		doom->swall->v1 == doom->swall->v2 || check_adjacent_wall(doom, doom->swall->v1, doom->swall->v2, doom->swall->sec))
		{
			doom->swall->v2 = -1;
			ft_putendl("Select valid vertex");
			return ;
		}
		doom->swall->wall2 = num_walls(doom, doom->swall->v2, doom->swall->sec);
		flip(doom, doom->swall);
		*doom->swall = (t_swall){ -1, -1, -1, -1, -1 };
		doom->sects->selected_sector = -1;
	}
	
}