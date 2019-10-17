/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_press.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 15:16:30 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/15 15:02:10 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void		mouse_press_right_part_two(t_doom *doom, int x, int y)
{
	if (x >= 1200 && x <= 1250 && y >= 110 && y <= 160)
	{
		if (doom->sects->sectors[doom->sects->selected_sector].floor <= 989)
			doom->sects->sectors[doom->sects->selected_sector].floor += 10;
	}
	else if (x >= 950 && x <= 1000 && y >= 510 && y <= 560)
	{
		if (doom->sects->sectors[doom->sects->selected_sector].light >= 10)
			doom->sects->sectors[doom->sects->selected_sector].light -= 10;
	}
	else if (x >= 1200 && x <= 1250 && y >= 510 && y <= 560)
	{
		if (doom->sects->sectors[doom->sects->selected_sector].light <= 90)
			doom->sects->sectors[doom->sects->selected_sector].light += 10;
	}
}

void		mouse_press_right(t_doom *doom, int x, int y)
{
	if (x >= 950 && x <= 1000 && y >= 60 && y <= 110)
	{
		if (doom->sects->sectors[doom->sects->selected_sector].ceiling >= 10)
			doom->sects->sectors[doom->sects->selected_sector].ceiling -= 10;
	}
	else if (x >= 1200 && x <= 1250 && y >= 60 && y <= 110)
	{
		if (doom->sects->sectors[doom->sects->selected_sector].ceiling <= 989)
			doom->sects->sectors[doom->sects->selected_sector].ceiling += 10;
	}
	else if (x >= 950 && x <= 1000 && y >= 110 && y <= 160)
	{
		if (doom->sects->sectors[doom->sects->selected_sector].floor >= 10)
			doom->sects->sectors[doom->sects->selected_sector].floor -= 10;
	}
	else
		mouse_press_right_part_two(doom, x, y);
}

void		mouse_press(t_doom *doom, t_sdl *sdl, int app)
{
	if (sdl->ev.button.button == SDL_BUTTON_LEFT && app == 2)
		mouse_press_left_two(doom, doom->sdl->ev.button.x,
		doom->sdl->ev.button.y);
	else if (sdl->ev.button.button == SDL_BUTTON_LEFT && app == 3)
		mouse_press_left_thr(doom, doom->sdl->ev.button.x,
		doom->sdl->ev.button.y);
	else if (sdl->ev.button.button == SDL_BUTTON_RIGHT && app == 2)
		mouse_press_right(doom, doom->sdl->ev.button.x,
		doom->sdl->ev.button.y);
}
