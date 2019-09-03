/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_select.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 16:45:32 by ohelly            #+#    #+#             */
/*   Updated: 2019/08/30 16:59:55 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		draw_select(t_doom *doom, t_mouse *mouse)
{
	mouse->ppos_x = 0;
	mouse->ppos_y = 0;
	while (mouse->ppos_x + doom->sh < mouse->x)
 		mouse->ppos_x += doom->sh;
  	while (mouse->ppos_y + doom->sh < mouse->y)
		mouse->ppos_y += doom->sh;
	if (mouse->ppos_x + (doom->sh / 2) > mouse->x && mouse->ppos_y + (doom->sh / 2) > mouse->y)
		;
	else if (mouse->ppos_x + (doom->sh / 2) > mouse->x && mouse->ppos_y + (doom->sh / 2) <= mouse->y)
		mouse->ppos_y += doom->sh / 2;
	else if (mouse->ppos_x + (doom->sh / 2) <= mouse->x && mouse->ppos_y + (doom->sh / 2) > mouse->y)
		mouse->ppos_x += doom->sh / 2;
	if (mouse->ppos_x != 0 && mouse->ppos_x != WIDTH && mouse->ppos_y != 0 && mouse->ppos_y != HEIGHT)
	{
		draw_rectangle(doom, mouse->ppos_x, mouse->ppos_y, 0x990000, 3);
	}
}

void		put_select(t_doom *doom, t_mouse *mouse)
{
	SDL_SetRenderDrawColor(doom->sdl->rend, 255, 0, 0, 0);
	draw_select(doom, mouse);
}