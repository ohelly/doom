/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadmenumain.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 15:33:53 by glormell          #+#    #+#             */
/*   Updated: 2019/10/29 20:27:09 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int					load_menu_button1(t_doom *doom, t_menu m)
{
	t_menu_button	*b;

	b = &doom->menu.btn1;
	b->p = (t_ab_i){ 0, 0 };
	b->s = (t_ab_i){ MENU_WIDTH, BTN_HEIGHT };
	b->h = 0;
	b->a = 0;
	b->d = 0;
	b->color = 0x00babc;
	b->h_color = (int)((b->color & 255) * 0.75) +
				((int)((b->color >> 8 & 255) * 0.75) << 8) +
				((int)((b->color >> 16 & 255) * 0.75) << 16);
	b->a_color = (int)((b->color & 255) * 0.6) +
				((int)((b->color >> 8 & 255) * 0.6) << 8) +
				((int)((b->color >> 16 & 255) * 0.6) << 16);
	b->d_color = 0xaaaaaa;
	b->he.f = doom->menu.font;
	b->he.t = "Button 1";
	load_hudel(&b->he);
	b->he.x = m.p.a + b->p.a + b->s.a / 2 - b->he.w / 2;
	b->he.y = m.p.b + b->p.b + b->s.b / 2 - b->he.h / 2;
	b->he.c = 0xffffff;
	b->he.b = 0;
	return (1);
}

int					load_menu_button2(t_doom *doom, t_menu m)
{
	t_menu_button	*b;

	b = &doom->menu.btn2;
	b->p = (t_ab_i){ 0, 0 };
	b->s = (t_ab_i){ MENU_WIDTH, BTN_HEIGHT };
	b->h = 0;
	b->a = 0;
	b->d = 0;
	b->color = 0x00babc;
	b->h_color = (int)((b->color & 255) * 0.75) +
				((int)((b->color >> 8 & 255) * 0.75) << 8) +
				((int)((b->color >> 16 & 255) * 0.75) << 16);
	b->a_color = (int)((b->color & 255) * 0.6) +
				((int)((b->color >> 8 & 255) * 0.6) << 8) +
				((int)((b->color >> 16 & 255) * 0.6) << 16);
	b->d_color = 0xaaaaaa;
	b->he.f = doom->menu.font;
	b->he.t = "Button 2";
	load_hudel(&b->he);
	b->he.x = m.p.a + b->p.a + b->s.a / 2 - b->he.w / 2;
	b->he.y = m.p.b + b->p.b + b->s.b / 2 - b->he.h / 2;
	b->he.c = 0xffffff;
	b->he.b = 0;
	return (1);
}

int					load_menu_button3(t_doom *doom, t_menu m)
{
	t_menu_button	*b;

	b = &doom->menu.btn3;
	b->p = (t_ab_i){ 0, 0 };
	b->s = (t_ab_i){ MENU_WIDTH, BTN_HEIGHT };
	b->h = 0;
	b->a = 0;
	b->d = 0;
	b->color = 0x00babc;
	b->h_color = (int)((b->color & 255) * 0.75) +
				((int)((b->color >> 8 & 255) * 0.75) << 8) +
				((int)((b->color >> 16 & 255) * 0.75) << 16);
	b->a_color = (int)((b->color & 255) * 0.6) +
				((int)((b->color >> 8 & 255) * 0.6) << 8) +
				((int)((b->color >> 16 & 255) * 0.6) << 16);
	b->d_color = 0xaaaaaa;
	b->he.f = doom->menu.font;
	b->he.t = "Button 3";
	load_hudel(&b->he);
	b->he.x = m.p.a + b->p.a + b->s.a / 2 - b->he.w / 2;
	b->he.y = m.p.b + b->p.b + b->s.b / 2 - b->he.h / 2;
	b->he.c = 0xffffff;
	b->he.b = 0;
	return (1);
}

int					load_menu_button4(t_doom *doom, t_menu m)
{
	t_menu_button	*b;

	b = &doom->menu.btn4;
	b->p = (t_ab_i){ 0, 0 };
	b->s = (t_ab_i){ MENU_WIDTH, BTN_HEIGHT };
	b->h = 0;
	b->a = 0;
	b->d = 0;
	b->color = 0x00babc;
	b->h_color = (int)((b->color & 255) * 0.75) +
				((int)((b->color >> 8 & 255) * 0.75) << 8) +
				((int)((b->color >> 16 & 255) * 0.75) << 16);
	b->a_color = (int)((b->color & 255) * 0.6) +
				((int)((b->color >> 8 & 255) * 0.6) << 8) +
				((int)((b->color >> 16 & 255) * 0.6) << 16);
	b->d_color = 0xaaaaaa;
	b->he.f = doom->menu.font;
	b->he.t = "Button 4";
	load_hudel(&b->he);
	b->he.x = m.p.a + b->p.a + b->s.a / 2 - b->he.w / 2;
	b->he.y = m.p.b + b->p.b + b->s.b / 2 - b->he.h / 2;
	b->he.c = 0xffffff;
	b->he.b = 0;
	return (1);
}

int					load_menu_button5(t_doom *doom, t_menu m)
{
	t_menu_button	*b;

	b = &doom->menu.btn5;
	b->p = (t_ab_i){ 0, 0 };
	b->s = (t_ab_i){ MENU_WIDTH, BTN_HEIGHT };
	b->h = 0;
	b->a = 0;
	b->d = 0;
	b->color = 0x00babc;
	b->h_color = (int)((b->color & 255) * 0.75) +
				((int)((b->color >> 8 & 255) * 0.75) << 8) +
				((int)((b->color >> 16 & 255) * 0.75) << 16);
	b->a_color = (int)((b->color & 255) * 0.6) +
				((int)((b->color >> 8 & 255) * 0.6) << 8) +
				((int)((b->color >> 16 & 255) * 0.6) << 16);
	b->d_color = 0xaaaaaa;
	b->he.f = doom->menu.font;
	b->he.t = "Button 5";
	load_hudel(&b->he);
	b->he.x = m.p.a + b->p.a + b->s.a / 2 - b->he.w / 2;
	b->he.y = m.p.b + b->p.b + b->s.b / 2 - b->he.h / 2;
	b->he.c = 0xffffff;
	b->he.b = 0;
	return (1);
}
