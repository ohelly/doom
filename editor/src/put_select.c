/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_select.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 16:45:32 by ohelly            #+#    #+#             */
/*   Updated: 2019/09/03 18:53:48 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		draw_select(t_doom *doom, t_mouse *mouse)
{
	mouse->ppos.x = 0;
	mouse->ppos.y = 0;
	while (mouse->ppos.x + doom->sh < mouse->pos.x)
 		mouse->ppos.x += doom->sh;
  	while (mouse->ppos.y + doom->sh < mouse->pos.y)
		mouse->ppos.y += doom->sh;
	if (mouse->ppos.x + (doom->sh / 2) > mouse->pos.x && mouse->ppos.y + (doom->sh / 2) > mouse->pos.y)
		;
	else if (mouse->ppos.x + (doom->sh / 2) > mouse->pos.x && mouse->ppos.y + (doom->sh / 2) <= mouse->pos.y)
		mouse->ppos.y += doom->sh / 2;
	else if (mouse->ppos.x + (doom->sh / 2) <= mouse->pos.x && mouse->ppos.y + (doom->sh / 2) > mouse->pos.y)
		mouse->ppos.x += doom->sh / 2;
	if (mouse->ppos.x != 0 && mouse->ppos.x != WIDTH && mouse->ppos.y != 0 && mouse->ppos.y != HEIGHT)
	{
		draw_rectangle(doom, mouse->ppos, 0x990000, 3);
	}
}

void		put_select(t_doom *doom, t_mouse *mouse)
{
	draw_select(doom, mouse);
}