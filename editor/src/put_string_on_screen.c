/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_string_on_screen.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 18:32:49 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/03 20:04:26 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void	rendermessage(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
	int 		w;
	int			h;
	SDL_Rect	dst;

	//SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	dst.x = x;
	dst.y = y;
	dst.w = 150;
	dst.h = 25;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

void	put_string_on_screen(t_doom *doom)
{
	static int		del = 0;

	doom->hud->color = (SDL_Color) { 0, 255, 0 };
	if (doom->app != 2)
		doom->hud->sur = TTF_RenderText_Solid(doom->hud->font, "Building mode", doom->hud->color);
	else
		doom->hud->sur = TTF_RenderText_Solid(doom->hud->font, "Edditing mode", doom->hud->color);
	doom->hud->string = SDL_CreateTextureFromSurface(doom->sdl->rend, doom->hud->sur);
	rendermessage(doom->hud->string, doom->sdl->rend, 22, 10);
	if (doom->hud->msg != 0)
	{
		if (del <= DELAY_ERR)
		{
			doom->hud->color = (SDL_Color) { 255, 0, 0 };
			doom->hud->sur = TTF_RenderText_Solid(doom->hud->font, doom->hud->msg, doom->hud->color);
			doom->hud->string = SDL_CreateTextureFromSurface(doom->sdl->rend, doom->hud->sur);
			rendermessage(doom->hud->string, doom->sdl->rend, 222, 10);
			del++;
		}
		else
		{
			del = 0;
			doom->hud->msg = 0;
		}
	}
}
