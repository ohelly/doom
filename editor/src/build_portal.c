/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_portal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 15:47:05 by ohelly            #+#    #+#             */
/*   Updated: 2019/09/19 17:50:13 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
**	Находит стену с вершинами, совпадающими со стеной w1
**	Возвращает индекс найденой стены, или -1 если такой стены нет
*/

int			get_duplicate_wall(t_doom *doom, t_wall w1)
{
	int		i;
	t_wall	w2;

	i = 0;
	while (i < doom->walls->count)
	{
		w2 = doom->walls->wall[i];
		if (((w1.vert_one == w2.vert_one && w1.vert_two == w2.vert_two) ||
			(w1.vert_one == w2.vert_two && w1.vert_two == w2.vert_one)) &&
			w1.sectors != w2.sectors)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

void		find_portal(t_doom *doom)
{
	int		ind;
	int		wall;
	t_wall	w1;
	t_wall	w2;

	ind = -1;
	if (doom->walls->selected_wall != -1)
	{
		doom->walls->selected_wall = -1;
		return ;
	}
	doom->walls->selected_wall = get_closest_wall(doom);
	wall = doom->walls->selected_wall;
	w1 = doom->walls->wall[wall];
	ind = get_duplicate_wall(doom, w1);
	if (ind != -1)
	{
		w2 = doom->walls->wall[ind];
		if (w1.portal == w2.sectors && w2.portal == w1.sectors)
		{
			ft_putendl("Press return to delete portal!");
			doom->walls->adjacent_wall = ind;
			return ;
		}
		else
		{
			ft_putendl("Press return to set portal!");
			doom->walls->adjacent_wall = ind;
			return ;
		}
	}
	doom->walls->adjacent_wall = -1;
	doom->walls->selected_wall = -1;
}

void		build_portal(t_doom *doom)
{
	int		sw;
	int		aw;

	if (doom->walls->selected_wall == -1)
		return ;
	sw = doom->walls->selected_wall;
	aw = doom->walls->adjacent_wall;
	if (doom->walls->wall[sw].portal == doom->walls->wall[aw].sectors &&
	doom->walls->wall[aw].portal == doom->walls->wall[sw].sectors)
	{
		doom->walls->wall[sw].portal = -1;
		doom->walls->wall[aw].portal = -1;
	}
	else
	{
		doom->walls->wall[sw].portal = doom->walls->wall[aw].sectors;
		doom->walls->wall[aw].portal = doom->walls->wall[sw].sectors;
	}
	doom->walls->selected_wall = -1;
	doom->walls->adjacent_wall = -1;
}