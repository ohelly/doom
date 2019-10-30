/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadmenu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 15:33:43 by glormell          #+#    #+#             */
/*   Updated: 2019/10/30 20:44:47 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void			load_buttons(t_doom *doom)
{
	t_menu_button	**b;

	b = &doom->menu.btns;
	*b = menu_button(doom, "Easy", 0x427533, 0xffffff);
	(*b)->click = menu_button1_click;
	b = &((*b)->next);
	*b = menu_button(doom, "Medium", 0x2B7C8C, 0xffffff);
	(*b)->click = menu_button2_click;
	b = &((*b)->next);
	*b = menu_button(doom, "Hard", 0x8C7535, 0xffffff);
	(*b)->click = menu_button3_click;
	b = &((*b)->next);
	*b = menu_button(doom, "Quit", 0x82352C, 0xffffff);
	(*b)->click = menu_button4_click;
	doom->menu.s_btn = 0;
}

int					load_menu(t_doom *doom)
{
	SDL_SetRelativeMouseMode(0);
	doom->menu.s = 0;
	doom->menu.c = 4;
	doom->menu.l = 0;
	doom->menu.i = HEIGHT / 3;
	doom->menu.h = HEIGHT - doom->menu.i * 2;
	doom->menu.p = (t_ab_i){ 0, 0 };
	load_buttons(doom);
	return (0);
}
