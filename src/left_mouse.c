/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 21:42:10 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/30 21:42:30 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		left_mouse(t_doom *doom, SDL_Event ev)
{
	if (doom->menu.s)
		menu_mouse(doom, 1);
	else
	{
		left_mouse_keydown(doom, ev,
		&doom->weapon[doom->player.weapon], &doom->player);
		if (ev.button.button == SDL_BUTTON_RIGHT)
			doom->rkey = 1;
	}
	return (0);
}
