/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 20:13:43 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/25 20:15:09 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

/*
** Возвращает количество стен данного сектора
*/

int		count_wall(t_doom *doom, int ind)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (++i < doom->walls->count)
		if (doom->walls->wall[i].sectors == ind)
			count++;
	return (count);
}

/*
** Возвращает номер верщины в сортированном порядке
*/

int		sorted_vert(t_doom *doom, int index)
{
	int i;

	i = 0;
	while (i < doom->verts->count)
	{
		if (doom->verts->list[i].num == index)
			return (i);
		i++;
	}
	return (-1);
}
