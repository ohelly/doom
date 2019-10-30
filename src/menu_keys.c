/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:47:50 by glormell          #+#    #+#             */
/*   Updated: 2019/10/30 20:11:59 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int		next_menu_button(t_doom *doom)
{
	if (!doom->menu.s_btn)
		doom->menu.s_btn = doom->menu.btns;
	else if (doom->menu.s_btn->next)
		doom->menu.s_btn = doom->menu.btns->next;
	return (0);
}

int				menu_keys(t_doom *doom, SDL_Event ev)
{
	if (ev.key.keysym.scancode == SDL_SCANCODE_RIGHT ||
			ev.key.keysym.scancode == SDL_SCANCODE_DOWN)
		return (next_menu_button(doom));
	else if (ev.key.keysym.scancode == SDL_SCANCODE_LEFT ||
			ev.key.keysym.scancode == SDL_SCANCODE_UP)
		return (0);
	return (0);
}
