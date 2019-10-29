/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_active.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 20:04:39 by glormell          #+#    #+#             */
/*   Updated: 2019/10/29 21:23:05 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		menu_active_button(t_menu_button *b, t_menu_button *ab)
{
	b->a = !b->d && ab == b;
}

void			menu_active(t_doom *doom, t_menu_button *ab)
{
	menu_active_button(&doom->menu.btn1, ab);
	menu_active_button(&doom->menu.btn2, ab);
	menu_active_button(&doom->menu.btn3, ab);
	menu_active_button(&doom->menu.btn4, ab);
	menu_active_button(&doom->menu.btn5, ab);
}
