/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 17:01:23 by ohelly            #+#    #+#             */
/*   Updated: 2019/09/08 20:37:52 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			output_pixel(t_doom *doom, int pos, int color)
{
	if (pos < 0 || pos >= WIDTH * HEIGHT)
		return (0);
	doom->sdl->pix[pos] = color;
	return (1);
}

int		draw_rectangle(t_doom *doom, t_v2 pos, int color, int size)
{
	int i;
	int j;
	int n;

	i = -size;
	while (i <= size)
	{
		j = -size;
		while (j <= size)
		{
			n = (pos.x + i) + (pos.y + j) * WIDTH;
			output_pixel(doom, n, color);
			doom->sdl->pix[n] = color;
			j++;
		}
		i++;
	}
	return (1);
}

/*
**	Рисует сектор по входящим в него вершинам
*/

void		draw_sector(t_doom *doom, t_sectors sector, int color)
{
	int			i;
	t_vertex	v1;
	t_vertex	v2;

	i = sector.start;
	while (i < sector.end)
	{
		v1 = doom->verts->list[doom->verts->order[i]];
		v2 = doom->verts->list[doom->verts->order[i + 1]];
		*doom->line = (t_line){v1.pos, v2.pos};
		line(doom, color);
		i++;
	}
	v1 = doom->verts->list[doom->verts->order[i]];
	v2 = doom->verts->list[doom->verts->order[sector.start]];
	*doom->line = (t_line){v1.pos, v2.pos};
	line(doom, color);
}

void		draw_wall(t_doom *doom, t_wall wall, int color)
{
	t_vertex v1;
	t_vertex v2;

	v1 = doom->verts->list[wall.vert_one];
	v2 = doom->verts->list[wall.vert_two];
	*doom->line = (t_line){v1.pos, v2.pos};
	line(doom, color);
}

void		draw_verts(t_doom *doom, int color)
{
	int			i;
	t_vertex	v;

	i = 0;
	while (i < doom->verts->count)
	{
		v = doom->verts->list[i];
		draw_rectangle(doom, v.pos, color, 2);
		i++;
	}
}

/*
**	Рисует линии между последними точками,
**	из которых еще не была сформированна стена
**	(Эта часть испытывает трудности из-за порядка вершин)
*/

void		draw_building_walls(t_doom *doom, int color)
{
	t_vertex	v1;
	t_vertex	v2;
	int			i;

	i = doom->verts->sel_v;
	while (i + 1 < doom->verts->i)
	{
		v1 = doom->verts->list[i];
		v2 = doom->verts->list[i + 1];
		*doom->line = (t_line){v1.pos, v2.pos, 0, 0};
		line(doom, color);
		i++;
	}
}

/*
**	Рисует линию между курсором и последней точкой
*/

void		draw_building_line(t_doom *doom, int color)
{
	t_vertex v;

	v = doom->verts->list[doom->verts->order[doom->verts->i_o - 1]];
	*doom->line = (t_line){v.pos, doom->mouse->ppos, 0, 0};
	line(doom, color);
}

void		draw_all(t_doom *doom)
{
	int i;
	int color;

	color = 0x990000;
	i = 0;
	while (i < doom->walls->count)
	{
		draw_wall(doom, doom->walls->wall[i], color);
		i++;
	}
	if (doom->app == 1)
	{
		draw_building_line(doom, color);
		draw_building_walls(doom, color);
	}
	draw_sector(doom, doom->sects->sectors[doom->sects->selected_sector], 0x009900);
	draw_verts(doom, 0xff0000);
}

void		output(t_doom *doom)
{
	bzero(doom->sdl->pix, WIDTH * HEIGHT * sizeof(Uint32));
	put_canvas(doom);
	put_select(doom, doom->mouse);
	draw_all(doom);
	SDL_UpdateTexture(doom->sdl->tex, NULL, doom->sdl->pix, WIDTH * sizeof(Uint32));
	SDL_RenderClear(doom->sdl->rend);
	SDL_RenderCopy(doom->sdl->rend, doom->sdl->tex, NULL, NULL);
	SDL_RenderPresent(doom->sdl->rend);
}