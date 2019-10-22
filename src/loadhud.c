/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadhud.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 20:36:12 by glormell          #+#    #+#             */
/*   Updated: 2019/10/22 19:35:40 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int		load_hudel(t_hudel *e)
{
	SDL_Color	color;

	color = (SDL_Color) { 255, 255, 255 };
	if (!(e->s = TTF_RenderText_Solid(e->f, e->t, color)))
		return (0);
	e->p = e->s->pixels;
	e->w = e->s->w;
	e->h = e->s->h;
}

static int		load_hud_health(t_doom *doom)
{
	t_hudel		*e;

	e = &doom->hud->health;
	e->f = doom->hud->font;
	e->t = "100%";
	load_hudel(e);
	e->x = 20;
	e->y = HEIGHT - e->h - 20;
	e->c = 0xf50f3f;
	e->b = 0x000000;
	return (1);
}

static int		load_hud_ammo(t_doom *doom)
{
	t_hudel		*e;

	e = &doom->hud->ammo;
	e->f = doom->hud->font;
	e->t = "30/30";
	load_hudel(e);
	e->x = WIDTH - e->w - 20;
	e->y = HEIGHT - e->h - 20;
	e->c = 0xf5f03f;
	e->b = 0x000000;
	return (1);
}

int				load_hud(t_doom *doom)
{
	if (!(load_hud_health(doom)) || !(load_hud_ammo(doom)))
		return (0);
	return (1);
}
