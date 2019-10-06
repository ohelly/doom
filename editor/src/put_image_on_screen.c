/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_image_on_screen.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 18:32:24 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/06 16:13:10 by ohelly           ###   ########.fr       */
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
		// < sector >
		renderTextures(doom->txt->huds[0], doom->sdl->rend, 950, 10, 50, 50);
		renderTextures(doom->txt->huds[1], doom->sdl->rend, 1200, 10, 50, 50);
		renderTextures(doom->txt->huds[2], doom->sdl->rend, 1000, 7, 200, 50);
		// < floor= >
		renderTextures(doom->txt->huds[0], doom->sdl->rend, 950, 60, 50, 50);
		renderTextures(doom->txt->huds[1], doom->sdl->rend, 1200, 60, 50, 50);
		renderTextures(doom->txt->huds[3], doom->sdl->rend, 1000, 57, 200, 50);
		// < ceiling= >
		renderTextures(doom->txt->huds[0], doom->sdl->rend, 950, 110, 50, 50);
		renderTextures(doom->txt->huds[1], doom->sdl->rend, 1200, 110, 50, 50);
		renderTextures(doom->txt->huds[4], doom->sdl->rend, 1000, 107, 200, 50);
		// < textures floor >
		renderTextures(doom->txt->huds[0], doom->sdl->rend, 950, 210, 50, 50);
		renderTextures(doom->txt->huds[1], doom->sdl->rend, 1200, 210, 50, 50);
		renderTextures(doom->txt->huds[5], doom->sdl->rend, 1000, 157, 200, 50);
		/*--*/
		// < textures ceiling >
		renderTextures(doom->txt->huds[0], doom->sdl->rend, 950, 310, 50, 50);
		renderTextures(doom->txt->huds[1], doom->sdl->rend, 1200, 310, 50, 50);
		renderTextures(doom->txt->huds[6], doom->sdl->rend, 1000, 257, 200, 50);
		/*--*/
		// skybox &
		renderTextures(doom->txt->huds[7], doom->sdl->rend, 1000, 357, 200, 50);
	}
}