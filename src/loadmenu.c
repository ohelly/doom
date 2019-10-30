/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadmenu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 15:33:43 by glormell          #+#    #+#             */
/*   Updated: 2019/10/30 17:17:42 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void			load_buttons(t_doom *doom)
{
	t_menu_button	**b;

	b = &doom->menu.btns;
	while (*b)
	{
		free(*b);
		b = &((*b)->next);
	}
	b = &doom->menu.btns;
	*b = menu_button(doom, "Button 1", 0x00babc, 0xffffff);
	(*b)->click = menu_button1_click;
	b = &((*b)->next);
	*b = menu_button(doom, "Ti pidor", 0xbabc00, 0x333333);
	(*b)->click = menu_button2_click;
	b = &((*b)->next);
	*b = menu_button(doom, "Quit", 0xba00bc, 0xaaaaaa);
	(*b)->click = menu_button3_click;
}

int					load_menu(t_doom *doom)
{
	SDL_SetRelativeMouseMode(0);
	doom->menu.s = 0;
	doom->menu.c = 3;
	doom->menu.l = 0;
	doom->menu.i = HEIGHT / 3;
	doom->menu.h = HEIGHT - doom->menu.i * 2;
	doom->menu.p = (t_ab_i){ 0, 0 };
	load_buttons(doom);
}
