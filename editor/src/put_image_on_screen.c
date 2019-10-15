/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_image_on_screen.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 18:32:24 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/15 19:46:31 by ohelly           ###   ########.fr       */
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
		// < skybox >
		renderTextures(doom->txt->huds[0], doom->sdl->rend, 650, 10, 50, 50);
		renderTextures(doom->txt->huds[1], doom->sdl->rend, 900, 10, 50, 50);
		renderTextures(doom->txt->huds[7], doom->sdl->rend, 700, 7, 200, 50);
		/*--*/
		// < sector >
		renderTextures(doom->txt->huds[0], doom->sdl->rend, 950, 10, 50, 50);
		renderTextures(doom->txt->huds[1], doom->sdl->rend, 1200, 10, 50, 50);
		renderTextures(doom->txt->huds[2], doom->sdl->rend, 1000, 7, 200, 50);
		// < ceiling= >
		renderTextures(doom->txt->huds[0], doom->sdl->rend, 950, 110, 50, 50);
		renderTextures(doom->txt->huds[1], doom->sdl->rend, 1200, 110, 50, 50);
		renderTextures(doom->txt->huds[3], doom->sdl->rend, 1000, 107, 200, 50);
		// < floor= >
		renderTextures(doom->txt->huds[0], doom->sdl->rend, 950, 60, 50, 50);
		renderTextures(doom->txt->huds[1], doom->sdl->rend, 1200, 60, 50, 50);
		renderTextures(doom->txt->huds[4], doom->sdl->rend, 1000, 57, 200, 50);
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
		if (doom->sects->sectors[doom->sects->selected_sector].skyb == 0 && doom->sects->selected_sector != -1)
			renderTextures(doom->txt->huds[8], doom->sdl->rend, 1200, 360, 50, 50);
		else if (doom->sects->sectors[doom->sects->selected_sector].skyb == 1 && doom->sects->selected_sector != -1)
			renderTextures(doom->txt->huds[9], doom->sdl->rend, 1200, 360, 50, 50);
		// door &
		renderTextures(doom->txt->huds[10], doom->sdl->rend, 1000, 407, 200, 50);
		if (doom->sects->sectors[doom->sects->selected_sector].door == 0 && doom->sects->selected_sector != -1)
			renderTextures(doom->txt->huds[8], doom->sdl->rend, 1200, 410, 50, 50);
		else if (doom->sects->sectors[doom->sects->selected_sector].door == 1 && doom->sects->selected_sector != -1)
			renderTextures(doom->txt->huds[9], doom->sdl->rend, 1200, 410, 50, 50);
		// window &
		renderTextures(doom->txt->huds[14], doom->sdl->rend, 1000, 457, 200, 50);
		if (doom->walls->wall[doom->walls->selected_wall].portal == -1 && doom->sects->selected_sector == -1)
			renderTextures(doom->txt->huds[8], doom->sdl->rend, 1200, 460, 50, 50);
		else if (doom->walls->wall[doom->walls->selected_wall].portal == -2 && doom->sects->selected_sector == -1)
			renderTextures(doom->txt->huds[9], doom->sdl->rend, 1200, 460, 50, 50);
		// < light >
		renderTextures(doom->txt->huds[0], doom->sdl->rend, 950, 510, 50, 50);
		renderTextures(doom->txt->huds[1], doom->sdl->rend, 1200, 510, 50, 50);
		renderTextures(doom->txt->huds[11], doom->sdl->rend, 1000, 507, 200, 50);
		// < wall >
		renderTextures(doom->txt->huds[0], doom->sdl->rend, 950, 560, 50, 50);
		renderTextures(doom->txt->huds[1], doom->sdl->rend, 1200, 560, 50, 50);
		renderTextures(doom->txt->huds[12], doom->sdl->rend, 1000, 557, 200, 50);
		// < textures wall >
		renderTextures(doom->txt->huds[0], doom->sdl->rend, 950, 660, 50, 50);
		renderTextures(doom->txt->huds[1], doom->sdl->rend, 1200, 660, 50, 50);
		renderTextures(doom->txt->huds[13], doom->sdl->rend, 1000, 607, 200, 50);
		renderTextures(doom->txt->wall[doom->walls->wall[doom->walls->selected_wall].txt], doom->sdl->rend, 1070, 657, 60, 50);
	}
	else if (doom->app == 3)
	{
		// < object >
		renderTextures(doom->txt->huds[0], doom->sdl->rend, 950, 10, 50, 50);
		renderTextures(doom->txt->huds[1], doom->sdl->rend, 1200, 10, 50, 50);
		renderTextures(doom->txt->huds[17], doom->sdl->rend, 1000, 7, 200, 50);
		// < texture obj >
		renderTextures(doom->txt->huds[0], doom->sdl->rend, 950, 60, 50, 50);
		renderTextures(doom->txt->huds[1], doom->sdl->rend, 1200, 60, 50, 50);
		/*--*/
		renderTextures(doom->txt->huds[0], doom->sdl->rend, 950, 110, 50, 50);
		renderTextures(doom->txt->huds[1], doom->sdl->rend, 1200, 110, 50, 50);
		renderTextures(doom->txt->huds[19], doom->sdl->rend, 1000, 107, 200, 50);
		// < texture sprite >
		renderTextures(doom->txt->huds[0], doom->sdl->rend, 950, 160, 50, 50);
		renderTextures(doom->txt->huds[1], doom->sdl->rend, 1200, 160, 50, 50);
		/*--*/
		// < height = >
		renderTextures(doom->txt->huds[0], doom->sdl->rend, 950, 210, 50, 50);
		renderTextures(doom->txt->huds[1], doom->sdl->rend, 1200, 210, 50, 50);
		renderTextures(doom->txt->huds[16], doom->sdl->rend, 1000, 207, 200, 50);
	}
}