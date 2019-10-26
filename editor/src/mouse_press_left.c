/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_press_left.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:46:49 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/23 19:26:52 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void		mouse_press_left_two(t_doom *doom, int x, int y)
{
	if ((x >= 950 && x <= 1000 && y >= 10 && y <= 60 && doom->sects->count > 1)
	|| (x > 1199 && x < 1251 && y > 9 && y < 61 && doom->sects->count > 1))
		sel_sector(x, y, doom->sects, doom->walls);
	else if ((x >= 950 && x <= 1000 && y >= 560 && y <= 610) ||
	(x >= 1200 && x <= 1250 && y >= 560 && y <= 610))
		sel_wall(x, y, doom->sects, doom->walls);
	else if ((x >= 1200 && x <= 1250 && y >= 360 && y <= 410) ||
	(x >= 1200 && x <= 1250 && y >= 460 && y <= 510) ||
	(x >= 1200 && x <= 1250 && y >= 410 && y <= 460))
		sel_attr(x, y, doom->sects, doom->walls);
	else if ((x >= 1200 && x <= 1250 && y >= 110 && y <= 160) ||
	(x >= 950 && x <= 1000 && y >= 110 && y <= 160))
		sel_floor(x, y, doom->sects);
	else if ((x >= 1200 && x <= 1250 && y >= 60 && y <= 110) ||
	(x >= 950 && x <= 1000 && y >= 60 && y <= 110))
		sel_ceiling(x, y, doom->sects);
	else if ((x >= 1200 && x <= 1250 && y >= 510 && y <= 560) ||
	(x >= 950 && x <= 1000 && y >= 510 && y <= 560))
		sel_light(x, y, doom->sects);
	else if ((x >= 950 && x <= 1000 && y >= 660 && y <= 710) ||
	(x >= 1200 && x <= 1250 && y >= 660 && y <= 710))
		sel_texture_wall(x, y, doom->walls);
	else if ((x >= 650 && x <= 710 && y >= 10 && y <= 60) ||
	(x >= 900 && x <= 950 && y >= 10 && y <= 60))
		change_skybox(x, y, doom->txt);
}

void		mouse_press_left_thr(t_doom *doom, int x, int y)
{
	if ((x >= 950 && x <= 1000 && y >= 10 && y <= 60)
	|| (x >= 1200 && x <= 1250 && y >= 10 && y <= 60))
		sel_object(x, y, doom->obj, doom->aspr);
	else if ((x > 949 && x < 1001 && y > 109 && y < 161) ||
	(x > 1199 && x < 1251 && y > 109 && y < 161))
		sel_sprite(x, y, doom->obj, doom->aspr);
	else if ((x >= 950 && x <= 1000 && y >= 210 && y <= 260) ||
	(x >= 1200 && x <= 1250 && y >= 210 && y <= 260))
		height_spr(x, y, doom->aspr, doom->sects);
}
