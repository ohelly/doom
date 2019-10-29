/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_string_on_screen.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 18:32:49 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/29 05:59:21 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void	hud_mode_render(int app, t_hud *hud, t_sdl *sdl)
{
	hud->color = (SDL_Color) { 0, 255, 0, 0 };
	if (app < 2)
		hud->sur = TTF_RenderText_Solid(hud->font, "Building mode", hud->color);
	else if (app == 2)
		hud->sur = TTF_RenderText_Solid(hud->font, "Edditing mode", hud->color);
	else if (app == 3)
		hud->sur = TTF_RenderText_Solid(hud->font,
		"Edditing object", hud->color);
	hud->string = SDL_CreateTextureFromSurface(sdl->rend, hud->sur);
	render_img(hud->string, sdl->rend, (t_scale) { { 22, 10 }, 150, 25 });
	SDL_FreeSurface(hud->sur);
}

void	error_render(t_hud *hud, t_sdl *sdl)
{
	static int	del = 0;

	if (del <= DELAY_ERR)
	{
		hud->color = (SDL_Color) { 255, 0, 0, 0 };
		hud->sur = TTF_RenderText_Solid(hud->font, hud->msg, hud->color);
		hud->string = SDL_CreateTextureFromSurface(sdl->rend, hud->sur);
		render_img(hud->string, sdl->rend, (t_scale) { { 222, 10 }, 150, 25 });
		SDL_FreeSurface(hud->sur);
		del++;
	}
	else
	{
		del = 0;
		hud->msg = 0;
	}
}

void	edditing_hud_render(t_all_sect *sects, t_hud *hud, t_sdl *sdl)
{
	if (sects->selected_sector == -1)
		return ;
	hud->color = (SDL_Color) { 0, 0, 0, 0 };
	my_itoa(hud->str, sects->sectors[sects->selected_sector].ceiling);
	hud->sur = TTF_RenderText_Solid(hud->font, hud->str, hud->color);
	hud->string = SDL_CreateTextureFromSurface(sdl->rend, hud->sur);
	render_img(hud->string, sdl->rend, (t_scale) { { 1160, 68 }, 35, 25 });
	SDL_FreeSurface(hud->sur);
	my_itoa(hud->str, sects->sectors[sects->selected_sector].floor);
	hud->sur = TTF_RenderText_Solid(hud->font, hud->str, hud->color);
	hud->string = SDL_CreateTextureFromSurface(sdl->rend, hud->sur);
	render_img(hud->string, sdl->rend, (t_scale) { { 1150, 118 }, 45, 25 });
	SDL_FreeSurface(hud->sur);
	my_itoa(hud->str, sects->sectors[sects->selected_sector].light);
	hud->sur = TTF_RenderText_Solid(hud->font, hud->str, hud->color);
	hud->string = SDL_CreateTextureFromSurface(sdl->rend, hud->sur);
	render_img(hud->string, sdl->rend, (t_scale) { { 1155, 518 }, 35, 25 });
	SDL_FreeSurface(hud->sur);
}

void	edditing_obj_render(t_all_spr_wall *aspr, t_hud *hud, t_sdl *sdl,
														t_player *player)
{
	hud->color = (SDL_Color) { 0, 0, 0, 0 };
	if (player->sec != -1)
	{
		my_itoa(hud->str, player->hp);
		hud->sur = TTF_RenderText_Solid(hud->font, hud->str, hud->color);
		hud->string = SDL_CreateTextureFromSurface(sdl->rend, hud->sur);
		render_img(hud->string, sdl->rend, (t_scale) {{1160, 415}, 35, 30 });
		SDL_FreeSurface(hud->sur);
	}
	if (aspr->select_spr == -1)
		return ;
	my_itoa(hud->str, aspr->spr[aspr->select_spr].z);
	hud->sur = TTF_RenderText_Solid(hud->font, hud->str, hud->color);
	hud->string = SDL_CreateTextureFromSurface(sdl->rend, hud->sur);
	render_img(hud->string, sdl->rend, (t_scale) { { 1159, 218 }, 35, 25 });
	SDL_FreeSurface(hud->sur);
}

void	put_string_on_screen(t_doom *doom)
{
	hud_mode_render(doom->app, doom->hud, doom->sdl);
	if (doom->hud->msg != 0)
		error_render(doom->hud, doom->sdl);
	if (doom->app == 2)
		edditing_hud_render(doom->sects, doom->hud, doom->sdl);
	else if (doom->app == 3)
		edditing_obj_render(doom->aspr, doom->hud, doom->sdl, doom->player);
}
