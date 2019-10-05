/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_image_on_screen.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 18:32:24 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/05 20:26:29 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void	renderTextures(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h)
{
	SDL_Rect	dst;

	//SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}


void		put_image_on_screen(t_doom *doom)
{
	renderTextures(doom->hud->text_for_app, doom->sdl->rend, 0, 0, 200, 50);
	renderTextures(doom->hud->text_for_app, doom->sdl->rend, 200, 0, 200, 50);
	if (doom->app == 2)
	{
		renderTextures(doom->txt->huds[0], doom->sdl->rend, 950, 10, 50, 50);
		renderTextures(doom->txt->huds[1], doom->sdl->rend, 1200, 10, 50, 50);
		renderTextures(doom->txt->huds[2], doom->sdl->rend, 1000, 7, 200, 50);
	}
}