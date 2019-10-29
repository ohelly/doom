/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadmenumain.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 15:33:53 by glormell          #+#    #+#             */
/*   Updated: 2019/10/29 18:22:24 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int			load_menu_main_button(t_doom *doom, t_menu m)
{
	t_menu_button	*b;

	b = &doom->menu.btn;
	b->p = (t_ab_i){ 0, 0 };
	b->s = (t_ab_i){ MENU_WIDTH, BTN_HEIGHT };
	b->h = 0;
	b->a = 0;
	b->d = 0;
	b->color = 0x00babc;
	b->h_color = 0x008889;
	b->a_color = 0x007778;
	b->d_color = 0xaaaaaa;
	b->he.f = doom->menu.font;
	b->he.t = "Button";
	load_hudel(&b->he);
	b->he.x = m.p.a + b->p.a + b->s.a / 2 - b->he.w / 2;
	b->he.y = m.p.b + b->p.b + b->s.b / 2 - b->he.h / 2;
	b->he.c = 0xffffff;
	b->he.b = 0;
	return (1);
}

int					load_menu_main(t_doom *doom)
{
	load_menu_main_button(doom, doom->menu);
	return (1);
}
