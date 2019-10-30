/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawscreen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 18:33:12 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/29 16:04:33 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			draw_screen(t_doom *doom)
{
	draw_walls(doom);
	drawsky(doom, doom->player, doom->sky, doom->img);
	drawsprites(doom, doom->objs);
	if (!doom->player.dead)
	{
		drawweapon(doom, &doom->weapon[doom->player.weapon]);
		draw_scope(doom->sdl);
	}
	drawhud(doom);
	draw_menu(doom);
	return (0);
}
