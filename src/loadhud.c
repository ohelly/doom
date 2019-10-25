/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadhud.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 20:36:12 by glormell          #+#    #+#             */
/*   Updated: 2019/10/24 18:47:22 by dtoy             ###   ########.fr       */
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
	//static int	hp = 100;

	e = &doom->hud->health;
	e->f = doom->hud->font;
	if (e->t)
		free(e->t);
	e->t = ft_strjoin(ft_itoa(doom->player.hp), "%");
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
	if (e->t)
		free(e->t);
	e->t = ft_itoa(doom->weapon[doom->player.weapon].ammo);
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
