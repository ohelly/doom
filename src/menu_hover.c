/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_hover.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 19:26:50 by glormell          #+#    #+#             */
/*   Updated: 2019/10/29 21:20:36 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		menu_hover_button(t_menu_button *b, t_menu_button *hb)
{
	b->h = !b->d && hb == b;
}

void			menu_hover(t_doom *doom, t_menu_button *hb)
{
	menu_hover_button(&doom->menu.btn1, hb);
	menu_hover_button(&doom->menu.btn2, hb);
	menu_hover_button(&doom->menu.btn3, hb);
	menu_hover_button(&doom->menu.btn4, hb);
	menu_hover_button(&doom->menu.btn5, hb);
}
