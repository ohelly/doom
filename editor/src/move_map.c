/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:30:12 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/22 18:48:33 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

/*
** Двигает спрайты
*/

void	move_spr(t_doom *doom)
{
	int		i;
	t_v2	move_v;

	move_v = (t_v2){doom->move_vector.x * 10, doom->move_vector.y * 10};
	doom->map_pos = v2_add(doom->map_pos, move_v);
	i = 0;
	while (i < doom->aspr->count)
	{
		doom->aspr->spr[i].pos = v2_add(doom->aspr->spr[i].pos, move_v);
		i++;
	}
}

/*
** Двигает объекты
*/

void	move_obj(t_doom *doom)
{
	int		i;
	t_v2	move_v;

	move_v = (t_v2){doom->move_vector.x * 10, doom->move_vector.y * 10};
	doom->map_pos = v2_add(doom->map_pos, move_v);
	i = 0;
	while (i < doom->obj->count)
	{
		doom->obj->obj[i].pos = v2_add(doom->obj->obj[i].pos, move_v);
		i++;
	}
	move_spr(doom);
}

/*
**	Двигает каждую вершину карты на move_vector
*/

int		move_map(t_doom *doom)
{
	int		i;
	t_v2	move_v;

	move_v = (t_v2){doom->move_vector.x * 10, doom->move_vector.y * 10};
	doom->map_pos = v2_add(doom->map_pos, move_v);
	i = 0;
	while (i < doom->verts->count)
	{
		doom->verts->list[i].pos = v2_add(doom->verts->list[i].pos, move_v);
		i++;
	}
	move_obj(doom);
	return (1);
}

/*
**	Функция отнимает от каждой позиции вершины doom->map_pos, чтобы
**	перевести координаты из позиции на экране в реальные координаты на карте.
**	Вызывать перед экспортом.
*/

int		vertices_return_map_pos(t_doom *doom)
{
	int		i;
	t_v2	subtract_v;

	subtract_v = (t_v2){doom->map_pos.x * -1, doom->map_pos.y * -1};
	i = 0;
	while (i < doom->verts->count)
	{
		doom->verts->list[i].pos = v2_add(doom->verts->list[i].pos, subtract_v);
		i++;
	}
	return (1);
}
