/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawscreen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 18:33:12 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/27 20:34:11 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			draw_screen(t_doom *doom)
{
	draw_walls(doom, doom->player);
	drawsky(doom, doom->player, doom->sky, doom->img);
	drawsprites(doom, doom->objs, doom->player);
	if (!doom->player.dead)
	{
		drawweapon(doom, &doom->weapon[doom->player.weapon]);
		draw_scope(doom->sdl);
	}
	drawhud(doom);
	return (0);
}
