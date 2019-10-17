/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadhud.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 20:36:12 by glormell          #+#    #+#             */
/*   Updated: 2019/10/17 20:55:49 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			load_hud(t_doom *doom)
{
	doom->hud->color = (SDL_Color) { 255, 255, 255 };
	if (!(doom->hud->sur = TTF_RenderText_Solid(doom->hud->font,
											"DRAW ME UP", doom->hud->color)))
		return (0);
	doom->hud->pix = (int *)doom->hud->sur->pixels;
	return (1);
}
