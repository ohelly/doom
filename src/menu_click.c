/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_click.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 19:22:32 by glormell          #+#    #+#             */
/*   Updated: 2019/10/29 21:17:38 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		menu_click_button(t_menu_button *b, t_menu_button *cb)
{
	b->a = 0;
	if (!b->d && cb == b)
		return ; // TODO: b->click();
}

void			menu_click(t_doom *doom, t_menu_button *cb)
{
	menu_click_button(&doom->menu.btn1, cb);
	menu_click_button(&doom->menu.btn2, cb);
	menu_click_button(&doom->menu.btn3, cb);
	menu_click_button(&doom->menu.btn4, cb);
	menu_click_button(&doom->menu.btn5, cb);
}
