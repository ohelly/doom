/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawhud.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:27:54 by glormell          #+#    #+#             */
/*   Updated: 2019/10/22 19:26:10 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		drawhudel(t_hudel e, int *pix)
{
	int			i;
	int			j;
	int			n;
	int			m;

	i = -1;
	while (++i < e.h)
	{
		j = -2;
		while (++j < e.w)
		{
			n = (e.y + i) * WIDTH + e.x + j;
			m = i * e.w + j;
			if (e.p[m] != 0 && j >= 0)
				pix[n] = e.c;
			else if ((j < 0 && e.p[m + 1] != 0) || (j >= 0 && (e.p[m + 1] != 0
					|| e.p[m - 1] != 0) && j + 1 < e.w && j - 1 >= 0) ||
					((e.p[m + e.w] != 0 || e.p[m - e.w] != 0) &&
					(i + 1 < e.h && i - 1 >= 0)))
				pix[n] = e.b;
		}
	}
}

void			drawhud(t_doom *doom)
{
	drawhudel(doom->hud->health, doom->sdl->pix);
	drawhudel(doom->hud->ammo, doom->sdl->pix);
}
