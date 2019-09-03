/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:43:25 by ohelly            #+#    #+#             */
/*   Updated: 2019/08/23 22:09:34 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		draw(t_doom *doom, t_line *line)
{
	SDL_RenderDrawPoint(doom->sdl->rend, line->x0, line->y0);
}

static int		ft_ifmin(int length, t_doom *doom, int lengthx, int lengthy)
{
	int d;

	d = -lengthx;
	while (--length)
	{
		draw(doom, doom->line);
		doom->line->x0 += doom->line->dx;
		d += 2 * lengthy;
		if (d > 0)
		{
			d -= 2 * lengthx;
			doom->line->y0 += doom->line->dy;
		}
	}
	return (0);
}

static int		ft_ifmax(int length, t_doom *doom, int lengthx, int lengthy)
{
	int d;

	d = -lengthy;
	while (--length)
	{
		draw(doom, doom->line);
		doom->line->y0 += doom->line->dy;
		d += 2 * lengthx;
		if (d > 0)
		{
			d -= 2 * lengthy;
			doom->line->x0 += doom->line->dx;
		}
	}
	return (0);
}

int				line(t_doom *doom)
{
	int lengthx;
	int lengthy;
	int length;

	lengthx = abs(doom->line->x1 - doom->line->x0);
	lengthy = abs(doom->line->y1 - doom->line->y0);
	length = fmax(lengthx, lengthy);
	doom->line->dx = (doom->line->x1 - doom->line->x0 >= 0 ? 1 : -1);
	doom->line->dy = (doom->line->y1 - doom->line->y0 >= 0 ? 1 : -1);
	if (length == 0)
		draw(doom, doom->line);
	if (lengthy <= lengthx)
		ft_ifmin(++length, doom, lengthx, lengthy);
	else
		ft_ifmax(++length, doom, lengthx, lengthy);
	return (0);
}
