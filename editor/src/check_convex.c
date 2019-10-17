/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_convex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 19:23:41 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/15 20:39:56 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

/*
** v1 - начальная
** v2 - следующая
** v3 - предыдущая
*/

int		check(t_v2 v1, t_v2 v2, t_v2 v3)
{
	double  sign;

	sign = ((v2.x - v3.x) * (v1.y - v3.y) - (v2.y - v3.y) * (v1.x - v3.x));
	printf("%f\n", sign);
	return (sign >= 0 ? 1 : 0);
}

int		check_convex(t_doom *doom)
{
	int		i;
	int		sign;

	sign = -1;
	i = -1;
	while (++i < doom->verts->built_v_count - 1)
	{
		if (sign == -1)
			sign = check(doom->verts->list[doom->verts->built_v_index[i]].pos, doom->verts->list[doom->verts->built_v_count - 1].pos, doom->verts->list[doom->verts->built_v_index[i + 1]].pos);
		else
		{
			if (sign != check(doom->verts->list[doom->verts->built_v_index[i]].pos, doom->verts->list[doom->verts->built_v_index[i + 1]].pos, doom->verts->list[doom->verts->built_v_index[i - 1]].pos))
			{
				doom->hud->msg = "Sector non convex";
				remove_built_sector(doom);
				printf("****\n");
				return (1);
			}
		}
	}
	printf("****\n");
	return (0);
}