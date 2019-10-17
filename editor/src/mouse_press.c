/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_press.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 15:16:30 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/17 15:42:08 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

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
