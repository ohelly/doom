/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_active.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 20:04:39 by glormell          #+#    #+#             */
/*   Updated: 2019/10/30 17:08:23 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void			menu_active_button(t_menu_button *b, t_menu_button *ab)
{
	b->a = !b->d && ab == b;
}

void				menu_active(t_doom *doom, t_menu_button *ab)
{
	t_menu_button	*b;

	b = doom->menu.btns;
	while (b)
	{
		menu_active_button(b, ab);
		b = b->next;
	}
}
