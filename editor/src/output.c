/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 17:01:23 by ohelly            #+#    #+#             */
/*   Updated: 2019/09/03 19:14:09 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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

int			output_pixel(t_doom *doom, int pos, int color)
{
	if (pos < 0 || pos >= WIDTH * HEIGHT)
		return (0);
	doom->sdl->pix[pos] = color;
	return (1);
}

void		draw_chto(t_doom *doom)
{
	int		i;

	i = 0;
	while (i + 1 < doom->verts->sel_v)
	{
		*doom->line = (t_line) { doom->verts->list[i].pos.x, doom->verts->list[i].pos.y, doom->verts->list[i + 1].pos.x, doom->verts->list[i + 1].pos.y, 0, 0 };
		line(doom, 0x990000);
		i++;
	}
	i = doom->verts->sel_v;
	while (i + 1 < doom->verts->i)
	{
		*doom->line = (t_line) { doom->verts->list[i].pos.x, doom->verts->list[i].pos.y, doom->verts->list[i + 1].pos.x, doom->verts->list[i + 1].pos.y, 0, 0 };
		line(doom, 0x990000);
		i++;
	}
	if (doom->app == 1)
	{
		*doom->line = (t_line) { doom->verts->list[doom->verts->i - 1].pos.x, doom->verts->list[doom->verts->i - 1].pos.y, doom->mouse->ppos.x, doom->mouse->ppos.y, 0, 0 };
		line(doom, 0x990000);
	}
}

void		output(t_doom *doom)
{
	bzero(doom->sdl->pix, WIDTH * HEIGHT * sizeof(Uint32));
	put_canvas(doom);
	put_select(doom, doom->mouse);
	draw_chto(doom);
	SDL_UpdateTexture(doom->sdl->tex, NULL, doom->sdl->pix, WIDTH * sizeof(Uint32));
	SDL_RenderClear(doom->sdl->rend);
	SDL_RenderCopy(doom->sdl->rend, doom->sdl->tex, NULL, NULL);
	SDL_RenderPresent(doom->sdl->rend);
}