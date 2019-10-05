/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 16:33:37 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/05 20:15:41 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

int		load_img_for_hud(t_doom *doom)
{
	if (!(doom->hud->text_for_app = IMG_LoadTexture(doom->sdl->rend, "img/hud/but.png")))
		return (0);
	if (!(doom->hud->font = TTF_OpenFont("fonts/font.ttf", 20)))
		return (0);
	if (!(doom->txt->huds[0] = IMG_LoadTexture(doom->sdl->rend, "img/hud/left.png")))
		return (0);
	if (!(doom->txt->huds[1] = IMG_LoadTexture(doom->sdl->rend, "img/hud/right.png")))
		return (0);
	if (!(doom->txt->huds[2] = IMG_LoadTexture(doom->sdl->rend, "img/hud/sector.png")))
		return (0);
	return (1);
}