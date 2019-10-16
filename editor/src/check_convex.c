/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_convex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 19:23:41 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/16 17:14:26 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

int		check_convex(t_doom *doom, int *ind, t_vertex *list)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (doom->verts->built_v_count <= 5)
		return (0);
	/*if (lines_intersect(list[0].pos, list[1].pos, list[0].pos, list[1].pos))
		printf("kek\n");*/
	while (++i < doom->verts->built_v_count - 1)
	{
		j = -1;
		while (++j < doom->verts->built_v_count - 1)
		{
			if (lines_intersect(list[i].pos, list[j].pos,))
			{
				doom->hud->msg = "Sector non convex";
				remove_built_sector(doom);
				return (1);
			}
		}
	}
	return (0);
}
