/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawmenu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 15:33:31 by glormell          #+#    #+#             */
/*   Updated: 2019/10/29 19:38:20 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void			draw_menu_button(t_doom *d, t_menu m, t_menu_button b)
{
	t_ab_i			p;
	t_ab_i			l;
	int				n;

	p = (t_ab_i){ m.p.a + b.p.a, m.p.b + b.p.b };
	l = (t_ab_i){ m.p.a + b.p.a + b.s.a, m.p.b + b.p.b + b.s.b };
	while (++p.b < l.b)
	{
		n = p.b * WIDTH;
		p.a = m.p.a + b.p.a;
		while (++p.a < l.a)
			if (b.d)
				d->sdl->pix[n + p.a] = b.d_color;
			else if (b.a)
				d->sdl->pix[n + p.a] = b.a_color;
			else
				d->sdl->pix[n + p.a] = b.h ? b.h_color : b.color;
	}
	drawhudel(b.he, d->sdl->pix);
}

static void			draw_menu_main(t_doom *doom)
{
	draw_menu_button(doom, doom->menu, doom->menu.btn);
}

static void			draw_menu_background(t_doom *doom)
{
	float			a;
	int				i;
	int				j;
	int				*p;

	a = 0.4;
	i = -1;
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
		{
			p = doom->sdl->pix + (i * WIDTH + j);
			*p = (int)((*p & 255) * a) +
				((int)((*p >> 8 & 255) * a) << 8) +
				((int)((*p >> 16 & 255) * a) << 16);
		}
	}
}

void				draw_menu(t_doom *doom)
{
	if (doom->menu.s)
	{
		draw_menu_background(doom);
		draw_menu_main(doom);
	}
}
