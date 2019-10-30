/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_click.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 19:22:32 by glormell          #+#    #+#             */
/*   Updated: 2019/10/30 14:43:36 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		menu_click_button(t_doom *doom,
									t_menu_button *b, t_menu_button *cb)
{
	if (!b->d && b->a && cb == b && b->click)
		b->click(doom, b);
	b->a = 0;
}

void			menu_click(t_doom *doom, t_menu_button *cb)
{
	menu_click_button(doom, &doom->menu.btn1, cb);
	menu_click_button(doom, &doom->menu.btn2, cb);
	menu_click_button(doom, &doom->menu.btn3, cb);
	menu_click_button(doom, &doom->menu.btn4, cb);
	menu_click_button(doom, &doom->menu.btn5, cb);
}
