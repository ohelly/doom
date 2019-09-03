/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_canvas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 22:07:45 by ohelly            #+#    #+#             */
/*   Updated: 2019/08/30 16:24:44 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		draw_canvas(t_doom *doom)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		*doom->line = (t_line){ x, y, WIDTH, y, 0, 0 };
		line(doom, 0x999999);
		y += doom->sh;
	}
	y = 0;
	while (x < WIDTH)
	{
		*doom->line = (t_line){ x, y, x, HEIGHT, 0, 0, };
		line(doom, 0x999999);
		x += doom->sh;
	}
}

void		put_canvas(t_doom *doom)
{
	draw_canvas(doom);
}