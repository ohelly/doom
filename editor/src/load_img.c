/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 16:33:37 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/03 19:23:17 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

int		load_img_for_hud(t_doom *doom)
{
	if (!(doom->hud->text_for_app = IMG_LoadTexture(doom->sdl->rend, "img/ladik.png")))
		return (0);
	if (!(doom->hud->font = TTF_OpenFont("/Library/Fonts/Arial.ttf", 20)))
		return (0);
	return (1);
}