/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawhud.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:27:54 by glormell          #+#    #+#             */
/*   Updated: 2019/10/17 20:52:10 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			drawhud(t_doom *doom)
{
	int			w;
	int			h;
	int			i;
	int			j;

	w = doom->hud->sur->w;
	h = doom->hud->sur->h;
	i = -1;
	while (++i < h)
	{
		j = -1;
		while (++j < w)
		{
			doom->sdl->pix[i * WIDTH + j] = doom->hud->pix[i * w + j];
		}
	}
			
}
