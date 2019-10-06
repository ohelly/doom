/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 16:33:37 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/06 16:12:44 by ohelly           ###   ########.fr       */
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
	if (!(doom->txt->huds[3] = IMG_LoadTexture(doom->sdl->rend, "img/hud/floor_.png")))
		return (0);
	if (!(doom->txt->huds[4] = IMG_LoadTexture(doom->sdl->rend, "img/hud/ceiling_.png")))
		return (0);
	if (!(doom->txt->huds[5] = IMG_LoadTexture(doom->sdl->rend, "img/hud/textures_floor.png")))
		return (0);
	if (!(doom->txt->huds[6] = IMG_LoadTexture(doom->sdl->rend, "img/hud/textures_ceiling.png")))
		return (0);
	if (!(doom->txt->huds[7] = IMG_LoadTexture(doom->sdl->rend, "img/hud/skybox.png")))
		return (0);
	if (!(doom->txt->huds[8] = IMG_LoadTexture(doom->sdl->rend, "img/hud/empty.png")))
		return (0);
	if (!(doom->txt->huds[9] = IMG_LoadTexture(doom->sdl->rend, "img/hud/sel.png")))
		return (0);
	return (1);
}