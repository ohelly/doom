/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 17:01:23 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/20 19:18:42 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

/*
**	Рисует вершины
*/

void		draw_verts(t_doom *doom, int color)
{
	int			i;
	t_vertex	v;

	i = -1;
	while (++i < doom->verts->count)
	{
		v = doom->verts->list[i];
		draw_rectangle(doom, v.pos, color, 2);
	}
	i = -1;
	while (++i < doom->walls->count && doom->sects->selected_sector != -1)
	{
		if (doom->walls->wall[i].sectors == doom->sects->selected_sector)
		{
			v = doom->verts->list[doom->walls->wall[i].vert_one];
			draw_rectangle(doom, v.pos, 0xffff00, 2);
		}
	}
	if (doom->verts->built_v_count > 0)
		draw_rectangle(doom, doom->verts->list
							[doom->verts->built_v_index[0]].pos, 0x999999, 3);
	if (doom->verts->projected_v.num != -1)
		draw_rectangle(doom, doom->verts->projected_v.pos, 0xffffff, 3);
}

void		draw_all(t_doom *doom)
{
	int i;
	int color;

	color = 0x990000;
	i = -1;
	while (++i < doom->walls->count)
	{
		if (doom->walls->wall[i].portal != -1 &&
			doom->sects->selected_sector != doom->walls->wall[i].sectors)
			draw_wall(doom, doom->walls->wall[i], 0xFFFF00);
		else
			draw_wall(doom, doom->walls->wall[i], 0x990000);
	}
	if (doom->app == 1)
	{
		draw_building_line(doom, color);
	}
	draw_sector(doom, doom->sects->selected_sector, 0x009900);
	if (doom->walls->selected_wall != -1)
		draw_wall(doom, doom->walls->wall[doom->walls->selected_wall],
																0x009900);
	draw_verts(doom, 0xff0000);
	draw_sprite(doom, 0x04ACFF);
}

void		output(t_doom *doom)
{
	bzero(doom->sdl->pix, WIDTH * HEIGHT * sizeof(Uint32));
	move_map(doom);
	put_canvas(doom);
	put_select(doom, doom->mouse);
	draw_all(doom);
	SDL_UpdateTexture(doom->sdl->tex, NULL, doom->sdl->pix,
												WIDTH * sizeof(Uint32));
	SDL_RenderClear(doom->sdl->rend);
	SDL_RenderCopy(doom->sdl->rend, doom->sdl->tex, NULL, NULL);
	put_image_on_screen(doom);
	put_string_on_screen(doom);
	SDL_RenderPresent(doom->sdl->rend);
}
