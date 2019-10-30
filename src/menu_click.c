/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_click.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 19:22:32 by glormell          #+#    #+#             */
/*   Updated: 2019/10/30 17:08:35 by glormell         ###   ########.fr       */
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
	t_menu_button	*b;

	b = doom->menu.btns;
	while (b)
	{
		menu_click_button(doom, b, cb);
		b = b->next;
	}
}
