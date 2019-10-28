/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:02:02 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/24 21:34:55 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

int		add_wall(t_doom *doom, int w1, int w2)
{
	doom->verts->count++;
	doom->walls->wall[doom->walls->count].vert_one = doom->verts->count - 1;
	doom->walls->wall[doom->walls->count].vert_two =
	doom->walls->wall[w1].vert_two;
	doom->walls->wall[doom->walls->count].sectors =
	doom->walls->wall[w1].sectors;
	doom->walls->wall[doom->walls->count].portal = -1;
	doom->walls->count++;
	doom->walls->wall[w1].vert_two = doom->verts->count - 1;
	if (w2 != -1)
	{
		doom->walls->wall[doom->walls->count].vert_one = doom->verts->count - 1;
		doom->walls->wall[doom->walls->count].vert_two =
		doom->walls->wall[w2].vert_two;
		doom->walls->wall[doom->walls->count].sectors =
		doom->walls->wall[w2].sectors;
		doom->walls->wall[doom->walls->count].portal = -1;
		doom->walls->wall[w2].vert_two = doom->verts->count - 1;
		doom->walls->count++;
	}
	doom->verts->projected_v.num = -1;
	return (1);
}

int		split_wall(t_doom *doom)
{
	int		i;
	int		w1;
	int		w2;
	t_v2	pos;

	if (doom->verts->projected_v.num == -1 || doom->app != 0)
		return (-1);
	w1 = doom->verts->projected_v.num;
	w2 = get_duplicate_wall(doom, doom->walls->wall[w1]);
	if (doom->walls->wall[w1].portal != -1 ||
	(w2 != -1 && doom->walls->wall[w2].portal != -1))
	{
		doom->hud->msg = "Error adding new vertex: remove portal first!";
		return (-1);
	}
	pos = doom->verts->projected_v.pos;
	i = doom->verts->count;
	doom->verts->list[i].pos = pos;
	return (add_wall(doom, w1, w2));
}
