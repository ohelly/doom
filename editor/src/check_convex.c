/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_convex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 19:23:41 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/24 19:33:52 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

int		error_and_remove_sector(t_doom *doom)
{
	doom->hud->msg = "Sector non convex";
	remove_built_sector(doom);
	return (1);
}

/*
** v1 - предыдущая
** v2 - начальная
** v3 - следующая
** Вычисляет в какую сторону двигаются сектора (по часовой или наоборот)
*/

int		scalar_product(t_v2 v1, t_v2 v2, t_v2 v3)
{
	return (((v3.x - v1.x) * (v2.y - v1.y) - (v3.y - v1.y) *
	(v2.x - v1.x)) > 0 ? 1 : 0);
}

/*
** Вернет единицу и удалит строящийся сектор если хотя бы один вектор сектора
** поменяет свое направление. Это будет значит что сектор невыпуклый.
** Работает с массивом строящихся вершин.
*/

int		check_convex(t_doom *doom, int *ind, t_vertex *list)
{
	int		i;
	int		sign;

	sign = -1;
	i = -1;
	if (doom->verts->built_v_count <= 4)
		return (0);
	while (++i < doom->verts->built_v_count - 2)
	{
		if (sign == -1)
			sign = scalar_product(list[ind[i]].pos, list[ind[i + 1]].pos,
			list[ind[i + 2]].pos);
		else
		{
			if (sign != scalar_product(list[ind[i]].pos, list[ind[i + 1]].pos,
			list[ind[i + 2]].pos))
				return (error_and_remove_sector(doom));
		}
	}
	if (sign != scalar_product(list[ind[i]].pos, list[ind[i + 1]].pos,
	list[ind[1]].pos))
		return (error_and_remove_sector(doom));
	return (0);
}
