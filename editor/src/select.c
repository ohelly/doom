/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:49:22 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/29 00:50:15 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

float	calc_dist(t_doom *doom, int vert1, int vert2, t_v2 *hit)
{
	t_v2 p1;
	t_v2 p2;
	t_v2 m;

	p1 = doom->verts->list[vert1].pos;
	p2 = doom->verts->list[vert2].pos;
	m = doom->mouse->pos;
	return (line_distance(p1, p2, m, hit));
}

void	get_closest_sector(t_doom *doom)
{
	int wall;

	if (doom->sects->selected_sector != -1)
	{
		doom->sects->selected_sector = -1;
		return ;
	}
	if (doom->walls->selected_wall != -1)
		doom->walls->selected_wall = -1;
	wall = get_closest_wall(doom);
	if (wall == -1)
	{
		doom->sects->selected_sector = -1;
		return ;
	}
	doom->sects->selected_sector = doom->walls->wall[wall].sectors;
}

int		get_closest_wall(t_doom *doom)
{
	t_closet	clos_wall;
	int			i;
	int			saved_wall;

	i = 0;
	saved_wall = -1;
	clos_wall.saved_dist = 1000;
	while (i < doom->walls->count)
	{
		clos_wall.curr_vertices.x = doom->walls->wall[i].vert_one;
		clos_wall.curr_vertices.y = doom->walls->wall[i].vert_two;
		clos_wall.dist = calc_dist(doom, clos_wall.curr_vertices.x,
		clos_wall.curr_vertices.y, &clos_wall.hit);
		if (clos_wall.dist < clos_wall.saved_dist)
		{
			saved_wall = i;
			clos_wall.saved_dist = clos_wall.dist;
			clos_wall.saved_hit = clos_wall.hit;
		}
		i++;
	}
	doom->verts->projected_v.num = saved_wall;
	doom->verts->projected_v.pos = clos_wall.saved_hit;
	return (saved_wall);
}
