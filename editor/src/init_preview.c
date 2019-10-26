/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_preview.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 18:53:05 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/26 19:11:20 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

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
		return (die_msg("Failed to load preview img"));
	return (1);
}