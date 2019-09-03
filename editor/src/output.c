/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 17:01:23 by ohelly            #+#    #+#             */
/*   Updated: 2019/09/03 16:44:01 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		draw_chto(t_doom *doom)
{
	int		i;

	i = 0;
	SDL_SetRenderDrawColor(doom->sdl->rend, 255, 0, 0, 0);
	while (i + 1 < doom->verts->sel_v)
	{
		*doom->line = (t_line) { doom->verts->list[i].x, doom->verts->list[i].y, doom->verts->list[i + 1].x, doom->verts->list[i + 1].y, 0, 0 };
		line(doom);
		i++;
	}
	i = doom->verts->sel_v;
	while (i + 1 < doom->verts->i)
	{
		*doom->line = (t_line) { doom->verts->list[i].x, doom->verts->list[i].y, doom->verts->list[i + 1].x, doom->verts->list[i + 1].y, 0, 0 };
		line(doom);
		i++;
	}
	if (doom->app == 1)
	{
		*doom->line = (t_line) { doom->verts->list[doom->verts->i - 1].x, doom->verts->list[doom->verts->i - 1].y, doom->mouse->ppos_x, doom->mouse->ppos_y, 0, 0 };
		line(doom);
	}
}

void		output(t_doom *doom)
{
	SDL_SetRenderDrawColor(doom->sdl->rend, 0, 0, 0, 0);
	SDL_RenderClear(doom->sdl->rend);
	put_canvas(doom);
	put_select(doom, doom->mouse);
	draw_chto(doom);
	SDL_RenderPresent(doom->sdl->rend);
}