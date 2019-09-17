/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_portal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 15:47:05 by ohelly            #+#    #+#             */
/*   Updated: 2019/09/17 18:04:38 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		find_portal(t_doom *doom)
{
	int		ind;
	int		wall;

	ind = -1;
	if (doom->walls->selected_wall != -1)
	{
		doom->walls->selected_wall = -1;
		return ;
	}
	doom->walls->selected_wall = get_closest_wall(doom);
	wall = doom->walls->selected_wall;
	while (++ind < doom->walls->count)
	{
		if ((doom->walls->wall[wall].vert_one == doom->walls->wall[ind].vert_one
		&& doom->walls->wall[wall].vert_two == doom->walls->wall[ind].vert_two &&
		doom->walls->wall[wall].sectors != doom->walls->wall[ind].sectors) ||
		(doom->walls->wall[wall].vert_one == doom->walls->wall[ind].vert_two &&
		doom->walls->wall[wall].vert_two == doom->walls->wall[ind].vert_one &&
		doom->walls->wall[wall].sectors != doom->walls->wall[ind].sectors))
		{
			ft_putendl("Press return for set portal!");
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
	doom->walls->wall[sw].portal = doom->walls->wall[aw].sectors;
	doom->walls->wall[aw].portal = doom->walls->wall[sw].sectors;
	doom->walls->selected_wall = -1;
	doom->walls->adjacent_wall = -1;
}