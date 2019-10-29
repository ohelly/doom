/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sky.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 13:34:25 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/29 13:46:19 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

int		load_sky(t_txt *txt, t_sdl *sdl)
{
	if (!(txt->sky[0] = IMG_LoadTexture(sdl->rend, "img/skybox/skybox1.png")))
		return (0);
	if (!(txt->sky[1] = IMG_LoadTexture(sdl->rend, "img/skybox/space.png")))
		return (0);
	if (!(txt->sky[2] = IMG_LoadTexture(sdl->rend, "img/skybox/space3.png")))
		return (0);
	if (!(txt->sky[3] = IMG_LoadTexture(sdl->rend, "img/skybox/space5.png")))
		return (0);
	return (1);
}
