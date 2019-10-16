/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:03:45 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/16 19:30:53 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

/*
** Меняет два значения, первому присваевает 0, второму -1
*/

void					sv(int *a, int *b)
{
	*a = 0;
	*b = -1;
}

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
			if (doom->walls->wall[i].vert_two == ver1 &&
			doom->walls->wall[i].vert_one == ver2)
				return (1);
	return (0);
}

int			check_portal(t_doom *doom)
{
	int		i;

	i = -1;
	if (doom->sects->selected_sector == -1)
		return (0);
	while (++i < doom->walls->count)
	{
		if (doom->walls->wall[i].sectors == doom->sects->selected_sector)
		{
			if (doom->walls->wall[i].portal != -1)
			{
				doom->hud->msg = "Remove portal";
				doom->sects->selected_sector = -1;
				return (1);
			}
		}
	}
	return (0);
}
