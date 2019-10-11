/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 16:33:37 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/11 15:39:49 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

int		load_img_for_hud(t_doom *doom)
{
	/*
		HUD 
			*/
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
	if (!(doom->txt->huds[10] = IMG_LoadTexture(doom->sdl->rend, "img/hud/door.png")))
		return (0);
	if (!(doom->txt->huds[11] = IMG_LoadTexture(doom->sdl->rend, "img/hud/light_.png")))
		return (0);
	if (!(doom->txt->huds[12] = IMG_LoadTexture(doom->sdl->rend, "img/hud/wall.png")))
		return (0);
	if (!(doom->txt->huds[13] = IMG_LoadTexture(doom->sdl->rend, "img/hud/textures_wall.png")))
		return (0);
	if (!(doom->txt->huds[14] = IMG_LoadTexture(doom->sdl->rend, "img/hud/window.png")))
		return (0);
	if (!(doom->txt->huds[15] = IMG_LoadTexture(doom->sdl->rend, "img/hud/end.png")))
		return (0);
	if (!(doom->txt->huds[16] = IMG_LoadTexture(doom->sdl->rend, "img/hud/height_.png")))
		return (0);
	if (!(doom->txt->huds[17] = IMG_LoadTexture(doom->sdl->rend, "img/hud/object.png")))
		return (0);
	if (!(doom->txt->huds[18] = IMG_LoadTexture(doom->sdl->rend, "img/hud/save.png")))
		return (0);
	if (!(doom->txt->huds[19] = IMG_LoadTexture(doom->sdl->rend, "img/hud/sprite.png")))
		return (0);
	if (!(doom->txt->huds[20] = IMG_LoadTexture(doom->sdl->rend, "img/hud/start.png")))
		return (0);
	/* 
		WALL
			*/
	if (!(doom->txt->wall[0] = IMG_LoadTexture(doom->sdl->rend, "img/wall/wall1.png")))
		return (0);
	if (!(doom->txt->wall[1] = IMG_LoadTexture(doom->sdl->rend, "img/wall/wall2.png")))
		return (0);
	if (!(doom->txt->wall[2] = IMG_LoadTexture(doom->sdl->rend, "img/wall/wall3.png")))
		return (0);
	if (!(doom->txt->wall[3] = IMG_LoadTexture(doom->sdl->rend, "img/wall/wall4.png")))
		return (0);
	if (!(doom->txt->wall[4] = IMG_LoadTexture(doom->sdl->rend, "img/wall/wall5.png")))
		return (0);
	if (!(doom->txt->wall[5] = IMG_LoadTexture(doom->sdl->rend, "img/wall/wall6.png")))
		return (0);
	if (!(doom->txt->wall[6] = IMG_LoadTexture(doom->sdl->rend, "img/wall/wall7.png")))
		return (0);
	if (!(doom->txt->wall[7] = IMG_LoadTexture(doom->sdl->rend, "img/wall/wall8.png")))
		return (0);
	if (!(doom->txt->wall[8] = IMG_LoadTexture(doom->sdl->rend, "img/wall/wall9.png")))
		return (0);
	if (!(doom->txt->wall[9] = IMG_LoadTexture(doom->sdl->rend, "img/wall/wall10.png")))
		return (0);
	if (!(doom->txt->wall[10] = IMG_LoadTexture(doom->sdl->rend, "img/wall/wall11.png")))
		return (0);
	if (!(doom->txt->wall[11] = IMG_LoadTexture(doom->sdl->rend, "img/wall/wall12.png")))
		return (0);
	if (!(doom->txt->wall[12] = IMG_LoadTexture(doom->sdl->rend, "img/wall/wall13.png")))
		return (0);
	if (!(doom->txt->wall[13] = IMG_LoadTexture(doom->sdl->rend, "img/wall/wall14.png")))
		return (0);
	if (!(doom->txt->wall[14] = IMG_LoadTexture(doom->sdl->rend, "img/wall/wall15.png")))
		return (0);
	if (!(doom->txt->wall[15] = IMG_LoadTexture(doom->sdl->rend, "img/wall/wall16.png")))
		return (0);
	if (!(doom->txt->wall[16] = IMG_LoadTexture(doom->sdl->rend, "img/wall/wall17.png")))
		return (0);
	if (!(doom->txt->wall[17] = IMG_LoadTexture(doom->sdl->rend, "img/wall/wall18.png")))
		return (0);
	if (!(doom->txt->wall[18] = IMG_LoadTexture(doom->sdl->rend, "img/wall/wall19.png")))
		return (0);
	if (!(doom->txt->wall[19] = IMG_LoadTexture(doom->sdl->rend, "img/wall/wall20.png")))
		return (0);
	if (!(doom->txt->wall[20] = IMG_LoadTexture(doom->sdl->rend, "img/wall/wall21.png")))
		return (0);
	return (1);
}