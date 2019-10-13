/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:43:25 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/13 18:52:06 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

static void		draw(t_doom *doom, t_line *line, int color)
{
	output_pixel(doom, line->pos0, color);
}

static int		ft_ifmin(int length, t_doom *doom, t_v2 length_v, int color)
{
	int d;

	d = -length_v.x;
	while (--length)
	{
		draw(doom, doom->line, color);
		doom->line->pos0.x += doom->line->d.x;
		d += 2 * length_v.y;
		if (d > 0)
		{
			d -= 2 * length_v.x;
			doom->line->pos0.y += doom->line->d.y;
		}
	}
	return (0);
}

static int		ft_ifmax(int length, t_doom *doom, t_v2 length_v, int color)
{
	int d;

	d = -length_v.y;
	while (--length)
	{
		draw(doom, doom->line, color);
		doom->line->pos0.y += doom->line->d.y;
		d += 2 * length_v.x;
		if (d > 0)
		{
			d -= 2 * length_v.y;
			doom->line->pos0.x += doom->line->d.x;
		}
	}
	return (0);
}

int				line(t_doom *doom, int color)
{
	t_v2	length_v;
	int		length;

	length_v.x = abs(doom->line->pos1.x - doom->line->pos0.x);
	length_v.y = abs(doom->line->pos1.y - doom->line->pos0.y);
	length = fmax(length_v.x, length_v.y);
	doom->line->d.x = (doom->line->pos1.x - doom->line->pos0.x >= 0 ? 1 : -1);
	doom->line->d.y = (doom->line->pos1.y - doom->line->pos0.y >= 0 ? 1 : -1);
	if (length == 0)
		draw(doom, doom->line, color);
	if (length_v.y <= length_v.x)
		ft_ifmin(++length, doom, length_v, color);
	else
		ft_ifmax(++length, doom, length_v, color);
	return (0);
}
