/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_hover.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 19:26:50 by glormell          #+#    #+#             */
/*   Updated: 2019/10/30 17:08:47 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		menu_hover_button(t_menu_button *b, t_menu_button *hb)
{
	b->h = !b->d && hb == b;
}

void			menu_hover(t_doom *doom, t_menu_button *hb)
{
	t_menu_button	*b;

	b = doom->menu.btns;
	while (b)
	{
		menu_hover_button(b, hb);
		b = b->next;
	}
}
