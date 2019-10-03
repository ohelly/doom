/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_image_on_screen.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 18:32:24 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/03 19:23:02 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void	renderTextures(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
	int 		w;
	int			h;
	SDL_Rect	dst;

	//SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	dst.x = x;
	dst.y = y;
	dst.w = 200;
	dst.h = 50;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}


void		put_image_on_screen(t_doom *doom)
{
	renderTextures(doom->hud->text_for_app, doom->sdl->rend, 0, 0);
	renderTextures(doom->hud->text_for_app, doom->sdl->rend, 200, 0);
}