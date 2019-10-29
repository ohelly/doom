/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawscreen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 18:33:12 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/29 17:25:03 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			draw_screen(t_doom *doom)
{
	//printf("1\n");
	draw_walls(doom);
	//printf("2\n");
	drawsky(doom, doom->player, doom->sky, doom->img);
	//printf("3\n");
	drawsprites(doom, doom->objs);
	//printf("4\n");
	if (!doom->player.dead)
	{
		drawweapon(doom, &doom->weapon[doom->player.weapon]);
	//	printf("5\n");
		draw_scope(doom->sdl);
	//	printf("6\n");
	}
	drawhud(doom);
//	printf("7\n");
	//printf("4\n");
	return (0);
}
