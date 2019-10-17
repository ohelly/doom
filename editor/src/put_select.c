/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_select.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 16:45:32 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/15 15:49:13 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

t_v2		magnet_to_vertex(t_doom *doom)
{
	int		i;
	float	dist;

	i = 0;
	while (i < doom->verts->count)
	{
		dist = distance(doom->verts->list[i].pos, doom->mouse->pos);
		if (dist < doom->sh / 2)
			return (doom->verts->list[i].pos);
		i++;
	}
	return ((t_v2){-1, -1});
}

void		draw_select(t_doom *doom, t_mouse *mouse)
{
	mouse->ppos = magnet_to_vertex(doom);
	if (mouse->ppos.x == -1 || mouse->ppos.y == -1)
	{
		mouse->ppos.x = mouse->pos.x - mouse->pos.x % (doom->sh / 2);
		mouse->ppos.y = mouse->pos.y - mouse->pos.y % (doom->sh / 2);
	}
	if (mouse->ppos.x >= 0 && mouse->ppos.x < WIDTH &&
		mouse->ppos.y >= 0 && mouse->ppos.y < HEIGHT)
	{
		draw_rectangle(doom, mouse->ppos, 0x990000, 3);
	}
}

void		put_select(t_doom *doom, t_mouse *mouse)
{
	draw_select(doom, mouse);
}
