/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_preview.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 18:53:05 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/29 13:34:08 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

int		init_previeww(t_txt *txt, t_sdl *sdl)
{
	if (!(txt->previeww[0] = IMG_LoadTexture(sdl->rend,
												"img/stobject/pistol.png")))
		return (0);
	if (!(txt->previeww[2] = IMG_LoadTexture(sdl->rend,
												"img/stobject/ripper.png")))
		return (0);
	if (!(txt->previeww[1] = IMG_LoadTexture(sdl->rend,
												"img/stobject/shotgun.png")))
		return (0);
	return (1);
}

int		init_previewo_p2(t_txt *txt, t_sdl *sdl)
{
	if (!(txt->previewo[9] = IMG_LoadTexture(sdl->rend,
													"img/stobject/ammo.png")))
		return (0);
	if (!(txt->previewo[10] = IMG_LoadTexture(sdl->rend,
												"img/stobject/pistol.png")))
		return (0);
	if (!(txt->previewo[11] = IMG_LoadTexture(sdl->rend,
												"img/stobject/ripper.png")))
		return (0);
	if (!(txt->previewo[12] = IMG_LoadTexture(sdl->rend,
												"img/stobject/shotgun.png")))
		return (0);
	if (!(txt->previewo[13] = IMG_LoadTexture(sdl->rend, "img/obj/3.png")))
		return (0);
	if (!(txt->previewo[14] = IMG_LoadTexture(sdl->rend, "img/obj/12.png")))
		return (0);
	if (!(txt->previewo[15] = IMG_LoadTexture(sdl->rend,
													"img/enemy/headN.png")))
		return (0);
	if (!(init_previeww(txt, sdl)))
		return (0);
	return (1);
}

int		init_previewo_p1(t_txt *txt, t_sdl *sdl)
{
	if (!(txt->previewo[0] = IMG_LoadTexture(sdl->rend, "img/stobject/1.png")))
		return (0);
	if (!(txt->previewo[1] = IMG_LoadTexture(sdl->rend, "img/stobject/2.png")))
		return (0);
	if (!(txt->previewo[2] = IMG_LoadTexture(sdl->rend, "img/stobject/7.png")))
		return (0);
	if (!(txt->previewo[3] = IMG_LoadTexture(sdl->rend, "img/stobject/8.png")))
		return (0);
	if (!(txt->previewo[4] = IMG_LoadTexture(sdl->rend, "img/stobject/9.png")))
		return (0);
	if (!(txt->previewo[5] = IMG_LoadTexture(sdl->rend, "img/stobject/10.png")))
		return (0);
	if (!(txt->previewo[6] = IMG_LoadTexture(sdl->rend, "img/stobject/11.png")))
		return (0);
	if (!(txt->previewo[7] = IMG_LoadTexture(sdl->rend, "img/stobject/14.png")))
		return (0);
	if (!(txt->previewo[8] = IMG_LoadTexture(sdl->rend,
													"img/stobject/card.png")))
		return (0);
	if (!(init_previewo_p2(txt, sdl)))
		return (0);
	return (1);
}

int		init_previews(t_txt *txt, t_sdl *sdl)
{
	if (!(txt->previews[0] = IMG_LoadTexture(sdl->rend,
													"img/stsprite/p1.png")))
		return (0);
	if (!(txt->previews[1] = IMG_LoadTexture(sdl->rend,
													"img/stsprite/p2.png")))
		return (0);
	if (!(txt->previews[2] = IMG_LoadTexture(sdl->rend,
													"img/stsprite/p3.png")))
		return (0);
	if (!(txt->previews[3] = IMG_LoadTexture(sdl->rend,
													"img/stsprite/p5.png")))
		return (0);
	if (!(txt->previews[4] = IMG_LoadTexture(sdl->rend, "img/sprite/t1.png")))
		return (0);
	if (!(txt->previews[5] = IMG_LoadTexture(sdl->rend, "img/sprite/v2.png")))
		return (0);
	return (1);
}

int		init_preview(t_doom *doom)
{
	if (!(init_previews(doom->txt, doom->sdl)))
		return (die_msg("Failed to load preview sprite img"));
	if (!(init_previewo_p1(doom->txt, doom->sdl)))
		return (die_msg("Faild to load preview object img"));
	if (!(load_sky(doom->txt, doom->sdl)))
		return (die_msg("Failed to load skybox img"));
	return (1);
}
