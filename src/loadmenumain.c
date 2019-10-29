/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadmenumain.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 15:33:53 by glormell          #+#    #+#             */
/*   Updated: 2019/10/29 22:21:52 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int					load_menu_button1(t_doom *doom, int v_insets)
{
	t_menu_button	*b;
	int				h;

	h = HEIGHT - v_insets * 2;
	b = &doom->menu.btn1;
	b->color = 0x00babc;
	b->he.t = "Button 1";
	load_menu_button(doom, b);
	b->p = (t_ab_i){ WIDTH / 2 - b->s.a / 2,
		v_insets + h / 5 * 1 - h / 10 - b->s.b / 2 };
	b->he.c = 0xffffff;
	load_menu_button_hudel(doom, b);
	b->click = menu_button1_click;
	return (1);
}

int					load_menu_button2(t_doom *doom, int v_insets)
{
	t_menu_button	*b;
	int				h;

	h = HEIGHT - v_insets * 2;
	b = &doom->menu.btn2;
	b->color = 0x00babc;
	b->he.t = "Button 2";
	load_menu_button(doom, b);
	b->p = (t_ab_i){ WIDTH / 2 - b->s.a / 2,
		v_insets + h / 5 * 2 - h / 10 - b->s.b / 2 };
	b->he.c = 0xffffff;
	load_menu_button_hudel(doom, b);
	b->click = menu_button2_click;
	return (1);
}

int					load_menu_button3(t_doom *doom, int v_insets)
{
	t_menu_button	*b;
	int				h;

	h = HEIGHT - v_insets * 2;
	b = &doom->menu.btn3;
	b->color = 0x00babc;
	b->he.t = "Button 3";
	load_menu_button(doom, b);
	b->p = (t_ab_i){ WIDTH / 2 - b->s.a / 2,
		v_insets + h / 5 * 3 - h / 10 - b->s.b / 2 };
	b->he.c = 0xffffff;
	load_menu_button_hudel(doom, b);
	b->click = menu_button3_click;
	return (1);
}

int					load_menu_button4(t_doom *doom, int v_insets)
{
	t_menu_button	*b;
	int				h;

	h = HEIGHT - v_insets * 2;
	b = &doom->menu.btn4;
	b->color = 0x00babc;
	b->he.t = "Button 4";
	load_menu_button(doom, b);
	b->p = (t_ab_i){ WIDTH / 2 - b->s.a / 2,
		v_insets + h / 5 * 4 - h / 10 - b->s.b / 2 };
	b->he.c = 0xffffff;
	load_menu_button_hudel(doom, b);
	b->click = menu_button4_click;
	return (1);
}

int					load_menu_button5(t_doom *doom, int v_insets)
{
	t_menu_button	*b;
	int				h;

	h = HEIGHT - v_insets * 2;
	b = &doom->menu.btn5;
	b->color = 0x00babc;
	b->he.t = "Button 5";
	load_menu_button(doom, b);
	b->p = (t_ab_i){ WIDTH / 2 - b->s.a / 2,
		v_insets + h / 5 * 5 - h / 10 - b->s.b / 2 };
	b->he.c = 0xffffff;
	load_menu_button_hudel(doom, b);
	b->click = menu_button5_click;
	return (1);
}
