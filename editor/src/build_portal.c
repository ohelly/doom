/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_portal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 15:47:05 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/29 00:51:33 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

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

int			toggle(t_doom *doom, t_wall *w1, int *ind)
{
	int		wall;

	if (doom->walls->selected_wall != -1)
	{
		doom->walls->selected_wall = -1;
		return (0);
	}
	if (doom->sects->selected_sector != -1)
		doom->sects->selected_sector = -1;
	doom->walls->selected_wall = get_closest_wall(doom);
	wall = doom->walls->selected_wall;
	*w1 = doom->walls->wall[wall];
	*ind = get_duplicate_wall(doom, *w1);
	return (1);
}

void		find_portal(t_doom *doom)
{
	int		ind;
	t_wall	w1;
	t_wall	w2;

	if (!(toggle(doom, &w1, &ind)))
		return ;
	if (ind != -1)
	{
		w2 = doom->walls->wall[ind];
		w1 = doom->walls->wall[doom->walls->selected_wall];
		if (w1.portal == w2.sectors && w2.portal == w1.sectors)
		{
			doom->hud->msg = "Press return to delete portal!";
			doom->walls->adjacent_wall = ind;
			return ;
		}
		else
		{
			doom->hud->msg = "Press return to set portal!";
			doom->walls->adjacent_wall = ind;
			return ;
		}
	}
	doom->walls->adjacent_wall = -1;
	doom->walls->selected_wall = -1;
}

/*
**	Проверяет, можно ли сделать портал между секторами s1 и s2
**	Возвращает -1 если портал уже существует, 1 если не существует
*/

int			can_build_portal(t_doom *doom, int s1, int s2)
{
	int	i;

	i = 0;
	while (i < doom->walls->count)
	{
		if ((doom->walls->wall[i].sectors == s1 &&
		doom->walls->wall[i].portal == s2) ||
		(doom->walls->wall[i].sectors == s2 &&
		doom->walls->wall[i].portal == s1))
			return (-1);
		i++;
	}
	return (1);
}

void		build_portal(t_doom *doom, int sw, int aw)
{
	if (doom->walls->selected_wall == -1)
		return ;
	if (check_sprite(doom, doom->walls->selected_wall,
									doom->walls->adjacent_wall))
		return ;
	if (doom->walls->wall[sw].portal == doom->walls->wall[aw].sectors &&
	doom->walls->wall[aw].portal == doom->walls->wall[sw].sectors)
	{
		doom->walls->wall[sw].portal = -1;
		doom->walls->wall[aw].portal = -1;
	}
	else
	{
		if (can_build_portal(doom, doom->walls->wall[aw].sectors,
		doom->walls->wall[sw].sectors) == -1)
			doom->hud->msg = "Portal between this two sectors already exists!";
		else
		{
			doom->walls->wall[sw].portal = doom->walls->wall[aw].sectors;
			doom->walls->wall[aw].portal = doom->walls->wall[sw].sectors;
		}
	}
	doom->walls->selected_wall = -1;
	doom->walls->adjacent_wall = -1;
}
