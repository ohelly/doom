/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 15:43:49 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/29 01:07:04 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

/*
** Рисует объекты и спрайты
*/

void		draw_sprite(t_doom *doom, int color)
{
	int		i;

	i = -1;
	while (++i < doom->aspr->count)
	{
		if (i == doom->aspr->select_spr)
			draw_rectangle(doom, doom->aspr->spr[i].pos, 0xffff00, 3);
		else
			draw_rectangle(doom, doom->aspr->spr[i].pos, color, 3);
	}
	i = -1;
	while (++i < doom->obj->count)
	{
		if (i == doom->obj->select_obj)
			draw_rectangle(doom, doom->obj->obj[i].pos, 0xffff00, 3);
		else
			draw_rectangle(doom, doom->obj->obj[i].pos, color, 3);
	}
}

/*
**	Рисует линию между курсором и последней точкой
*/

void		draw_building_line(t_doom *doom, int color)
{
	t_vertex v;

	v = doom->verts->list[doom->verts->built_v_index
							[doom->verts->built_v_count - 1]];
	*doom->line = (t_line){v.pos, doom->mouse->ppos, { 0, 0 } };
	line(doom, color);
}

/*
**	Рисует сектор по входящим в него вершинам
*/

void		draw_sector(t_doom *doom, int sector, int color)
{
	int			i;
	t_wall		w;

	if (sector == -1)
		return ;
	i = 0;
	while (i < doom->walls->count)
	{
		w = doom->walls->wall[i];
		if (w.sectors == sector)
			draw_wall(doom, w, color);
		i++;
	}
}

/*
** Рисует стену
*/

void		draw_wall(t_doom *doom, t_wall wall, int color)
{
	t_vertex v1;
	t_vertex v2;

	v1 = doom->verts->list[wall.vert_one];
	v2 = doom->verts->list[wall.vert_two];
	*doom->line = (t_line){v1.pos, v2.pos, { 0, 0 }};
	line(doom, color);
}

/*
**	Рисует квадратик размером size
*/

int			draw_rectangle(t_doom *doom, t_v2 pos, int color, int size)
{
	int i;
	int j;

	i = -size;
	while (i <= size)
	{
		j = -size;
		while (j <= size)
		{
			output_pixel(doom, (t_v2){pos.x + i, pos.y + j}, color);
			j++;
		}
		i++;
	}
	return (1);
}
