/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadmenubuttons.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:00:43 by glormell          #+#    #+#             */
/*   Updated: 2019/10/30 20:46:03 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void			load_menu_button_hudel(t_doom *doom, t_menu_button *b)
{
	t_hudel		*e;
	t_menu		m;
	SDL_Color	color;

	e = &b->he;
	m = doom->menu;
	color = (SDL_Color) { 255, 255, 255, 0};
	SDL_FreeSurface(e->s);
	if (!(e->s = TTF_RenderText_Solid(e->f, e->t, color)))
		return ;
	e->p = e->s->pixels;
	e->w = e->s->w;
	e->h = e->s->h;
	b->he.x = m.p.a + b->p.a + b->s.a / 2 - b->he.w / 2;
	b->he.y = m.p.b + b->p.b + b->s.b / 2 - b->he.h / 2;
}

static void			load_menu_button(t_doom *doom, t_menu_button *b)
{
	b->s = (t_ab_i){ MENU_WIDTH, BTN_HEIGHT };
	b->p = (t_ab_i){ WIDTH / 2 - b->s.a / 2,
		doom->menu.i + doom->menu.h / doom->menu.c * doom->menu.l -
			doom->menu.h / doom->menu.c / 2 - b->s.b / 2 };
	b->h = 0;
	b->a = 0;
	b->d = 0;
	b->s_color = (int)((b->color & 255) * 1.25) +
				((int)((b->color >> 8 & 255) * 1.25) << 8) +
				((int)((b->color >> 16 & 255) * 1.25) << 16);
	b->h_color = (int)((b->color & 255) * 0.75) +
				((int)((b->color >> 8 & 255) * 0.75) << 8) +
				((int)((b->color >> 16 & 255) * 0.75) << 16);
	b->a_color = (int)((b->color & 255) * 0.6) +
				((int)((b->color >> 8 & 255) * 0.6) << 8) +
				((int)((b->color >> 16 & 255) * 0.6) << 16);
	b->d_color = 0xaaaaaa;
	b->he.f = doom->menu.font;
	b->he.b = 0;
	b->click = 0;
	b->next = 0;
}

t_menu_button		*menu_button(t_doom *doom, char *title, int color,
		int he_color)
{
	t_menu_button	*b;

	b = (t_menu_button *)ft_memalloc(sizeof(t_menu_button));
	++doom->menu.l;
	b->he.t = title;
	b->color = color;
	load_menu_button(doom, b);
	b->he.c = he_color;
	load_menu_button_hudel(doom, b);
	return (b);
}
