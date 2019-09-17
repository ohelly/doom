/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_canvas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 22:07:45 by ohelly            #+#    #+#             */
/*   Updated: 2019/09/03 18:49:47 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			draw_grid(t_doom *doom)
{
	int x;
	int y;

	y = (doom->map_pos.y % doom->sh == 0) ? 0 : doom->sh / 2;
	while (y < HEIGHT)
	{
		*doom->line = (t_line){ 0, y, WIDTH, y, 0, 0 };
		line(doom, 0x999999);
		y += doom->sh;
	}
	x = (doom->map_pos.x % doom->sh == 0) ? 0 : doom->sh / 2;
	while (x < WIDTH)
	{
		*doom->line = (t_line){ x, 0, x, HEIGHT, 0, 0 };
		line(doom, 0x999999);
		x += doom->sh;
	}
}

void		put_canvas(t_doom *doom)
{
	draw_grid(doom);
}