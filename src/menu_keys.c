/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:47:50 by glormell          #+#    #+#             */
/*   Updated: 2019/10/30 20:35:08 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int			next_menu_button(t_doom *doom)
{
	if (!doom->menu.s_btn || !doom->menu.s_btn->next)
		doom->menu.s_btn = doom->menu.btns;
	else if (doom->menu.s_btn->next)
		doom->menu.s_btn = doom->menu.s_btn->next;
	return (0);
}

static int			prev_menu_button(t_doom *doom)
{
	t_menu_button	*b;

	b = doom->menu.s_btn;
	if (!b || b == doom->menu.btns)
	{
		doom->menu.s_btn = doom->menu.btns;
		while (doom->menu.s_btn->next)
			doom->menu.s_btn = doom->menu.s_btn->next;
	}
	else
	{
		doom->menu.s_btn = doom->menu.btns;
		while (doom->menu.s_btn->next != b)
			doom->menu.s_btn = doom->menu.s_btn->next;
	}
	return (0);
}

static int			choose_menu_button(t_doom *doom)
{
	if (doom->menu.s_btn->click)
		doom->menu.s_btn->click(doom, doom->menu.s_btn);
	return (0);
}

int					menu_keys(t_doom *doom, SDL_Event ev)
{
	if (ev.key.keysym.scancode == SDL_SCANCODE_RIGHT ||
			ev.key.keysym.scancode == SDL_SCANCODE_DOWN)
		return (next_menu_button(doom));
	else if (ev.key.keysym.scancode == SDL_SCANCODE_LEFT ||
			ev.key.keysym.scancode == SDL_SCANCODE_UP)
		return (prev_menu_button(doom));
	else if (ev.key.keysym.scancode == SDL_SCANCODE_RETURN)
		return (choose_menu_button(doom));
	return (0);
}
