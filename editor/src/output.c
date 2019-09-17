/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 17:01:23 by ohelly            #+#    #+#             */
/*   Updated: 2019/09/17 17:53:08 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			output_pixel(t_doom *doom, t_v2 pos, int color)
{
	int position;

	if (v2_in_borders(pos, WIDTH, HEIGHT) == 0)
		return (0);
	position = pos.x + pos.y * WIDTH;
	doom->sdl->pix[position] = color;
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
			output_pixel(doom, (t_v2){pos.x + i, pos.y + j}, color);
			j++;
		}
		i++;
	}
	return (1);
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
	draw_rectangle(doom, doom->verts->projected_v, 0xffffff, 3);
}

void		draw_wall(t_doom *doom, t_wall wall, int color)
{
	t_vertex v1;
	t_vertex v2;

	v1 = doom->verts->list[wall.vert_one];
	v2 = doom->verts->list[wall.vert_two];
	*doom->line = (t_line){v1.pos, v2.pos};
	if (wall.portal != -1)
		line(doom, 0xFFFF00);
	else
		line(doom, color);
}

/*
**	Рисует сектор по входящим в него вершинам
*/

void		draw_sector(t_doom *doom, int sector, int color)
{
	int			i;
	t_wall		w;
	t_vertex	v1;
	t_vertex	v2;

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
**	Рисует линию между курсором и последней точкой
*/

void		draw_building_line(t_doom *doom, int color)
{
	t_vertex v;

	v = doom->verts->list[doom->verts->built_v_index[doom->verts->built_v_count - 1]];
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
	}
	draw_sector(doom, doom->sects->selected_sector, 0x009900);
	if (doom->walls->selected_wall != -1)
		draw_wall(doom, doom->walls->wall[doom->walls->selected_wall], 0x009900);
	draw_verts(doom, 0xff0000);
}

void		output(t_doom *doom)
{
	bzero(doom->sdl->pix, WIDTH * HEIGHT * sizeof(Uint32));
	move_map(doom);
	put_canvas(doom);
	put_select(doom, doom->mouse);
	draw_all(doom);
	SDL_UpdateTexture(doom->sdl->tex, NULL, doom->sdl->pix, WIDTH * sizeof(Uint32));
	SDL_RenderClear(doom->sdl->rend);
	SDL_RenderCopy(doom->sdl->rend, doom->sdl->tex, NULL, NULL);
	SDL_RenderPresent(doom->sdl->rend);
}