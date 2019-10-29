/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadmenu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 15:33:43 by glormell          #+#    #+#             */
/*   Updated: 2019/10/29 21:08:35 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		load_menu_button(t_doom *doom, t_menu_button *b)
{
	t_menu	m;

	m = doom->menu;
	b->s = (t_ab_i){ MENU_WIDTH, BTN_HEIGHT };
	b->h = 0;
	b->a = 0;
	b->d = 0;
	b->h_color = (int)((b->color & 255) * 0.75) +
				((int)((b->color >> 8 & 255) * 0.75) << 8) +
				((int)((b->color >> 16 & 255) * 0.75) << 16);
	b->a_color = (int)((b->color & 255) * 0.6) +
				((int)((b->color >> 8 & 255) * 0.6) << 8) +
				((int)((b->color >> 16 & 255) * 0.6) << 16);
	b->d_color = 0xaaaaaa;
	b->he.f = doom->menu.font;
	b->he.x = m.p.a + b->p.a + b->s.a / 2 - b->he.w / 2;
	b->he.y = m.p.b + b->p.b + b->s.b / 2 - b->he.h / 2;
	b->he.b = 0;
}

int			load_menu(t_doom *doom)
{
	SDL_SetRelativeMouseMode(0);
	doom->menu.s = 0;
	doom->menu.p = (t_ab_i){ 20, 20 };
	load_menu_button1(doom);
	load_menu_button2(doom);
	load_menu_button3(doom);
	load_menu_button4(doom);
	load_menu_button5(doom);
}
