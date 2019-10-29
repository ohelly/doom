/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadmenumain.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 15:33:53 by glormell          #+#    #+#             */
/*   Updated: 2019/10/29 21:09:31 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int					load_menu_button1(t_doom *doom)
{
	t_menu_button	*b;

	b = &doom->menu.btn1;
	b->color = 0x00babc;
	b->he.t = "Button 1";
	load_menu_button(doom, b);
	b->p = (t_ab_i){ WIDTH / 2 - b->s.a / 2, HEIGHT / 5 * 1 / 2 - b->s.b / 2 };
	b->he.c = 0xffffff;
	load_hudel(&b->he);
	return (1);
}

int					load_menu_button2(t_doom *doom)
{
	t_menu_button	*b;

	b = &doom->menu.btn2;
	b->color = 0x00babc;
	b->he.t = "Button 2";
	load_menu_button(doom, b);
	b->p = (t_ab_i){ WIDTH / 2 - b->s.a / 2, HEIGHT / 5 * 2 / 2 - b->s.b / 2 };
	b->he.c = 0xffffff;
	load_hudel(&b->he);
	return (1);
}

int					load_menu_button3(t_doom *doom)
{
	t_menu_button	*b;

	b = &doom->menu.btn3;
	b->color = 0x00babc;
	b->he.t = "Button 3";
	load_menu_button(doom, b);
	b->p = (t_ab_i){ WIDTH / 2 - b->s.a / 2, HEIGHT / 5 * 3 / 2 - b->s.b / 2 };
	b->he.c = 0xffffff;
	load_hudel(&b->he);
	return (1);
}

int					load_menu_button4(t_doom *doom)
{
	t_menu_button	*b;

	b = &doom->menu.btn4;
	b->color = 0x00babc;
	b->he.t = "Button 4";
	load_menu_button(doom, b);
	b->p = (t_ab_i){ WIDTH / 2 - b->s.a / 2, HEIGHT / 5 * 4 / 2 - b->s.b / 2 };
	b->he.c = 0xffffff;
	load_hudel(&b->he);
	return (1);
}

int					load_menu_button5(t_doom *doom)
{
	t_menu_button	*b;

	b = &doom->menu.btn5;
	b->color = 0x00babc;
	b->he.t = "Button 5";
	load_menu_button(doom, b);
	b->p = (t_ab_i){ WIDTH / 2 - b->s.a / 2, HEIGHT / 5 * 5 / 2 - b->s.b / 2 };
	b->he.c = 0xffffff;
	load_hudel(&b->he);
	return (1);
}
