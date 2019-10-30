/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 19:08:42 by glormell          #+#    #+#             */
/*   Updated: 2019/10/30 17:09:03 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static t_menu_button	*is_menu_button(t_doom *d, t_ab_i p, t_menu_button *b)
{
	t_menu				m;

	m = d->menu;
	if (p.a > m.p.a + b->p.a && p.a <= m.p.a + b->p.a + b->s.a &&
		p.b > m.p.b + b->p.b && p.b <= m.p.b + b->p.b + b->s.b)
		return (b);
	return (0);
}

static t_menu_button	*is_main_menu(t_doom *doom, t_ab_i p)
{
	t_menu_button		*b;

	b = doom->menu.btns;
	while (b)
	{
		if (is_menu_button(doom, p, b))
			return (b);
		b = b->next;
	}
	return (0);
}

static t_menu_button	*is_menu(t_doom *doom, t_ab_i p)
{
	t_menu_button		*r;

	if ((r = is_main_menu(doom, p)))
		return (r);
	return (0);
}

void					menu_mouse(t_doom *doom, int o)
{
	t_menu_button		*b;
	int					x;
	int					y;

	SDL_GetMouseState(&x, &y);
	b = is_menu(doom, (t_ab_i){ x, y });
	if (o == 0)
		menu_hover(doom, b);
	else if (o == 1)
		menu_active(doom, b);
	else if (o == 2)
		menu_click(doom, b);
}
