/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edditing_img_render.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 12:36:00 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/18 14:55:21 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void	sky(t_txt *txt, t_sdl *sdl, t_all_sect *sects)
{
	render_img(txt->huds[7], sdl->rend, (t_scale) { 1000, 357, 200, 50 });
	if (sects->sectors[sects->selected_sector].skyb == 0 &&
												sects->selected_sector != -1)
		render_img(txt->huds[8], sdl->rend, (t_scale) { 1200, 360, 50, 50 });
	else if (sects->sectors[sects->selected_sector].skyb == 1 &&
												sects->selected_sector != -1)
		render_img(txt->huds[9], sdl->rend, (t_scale) { 1200, 360, 50, 50});
}

void	door(t_txt *txt, t_sdl *sdl, t_all_sect *sects)
{
	render_img(txt->huds[10], sdl->rend, (t_scale) { 1000, 407, 200, 50 });
	if (sects->sectors[sects->selected_sector].door == 0 &&
												sects->selected_sector != -1)
		render_img(txt->huds[8], sdl->rend, (t_scale) { 1200, 410, 50, 50 });
	else if (sects->sectors[sects->selected_sector].door == 1 &&
												sects->selected_sector != -1)
		render_img(txt->huds[9], sdl->rend, (t_scale) { 1200, 410, 50, 50 });
}

void	window(t_txt *txt, t_sdl *sdl, t_all_walls *walls, t_all_sect *sects)
{
	render_img(txt->huds[14], sdl->rend, (t_scale) { 1000, 457, 200, 50 });
	if (walls->wall[walls->selected_wall].portal == -1 &&
												sects->selected_sector == -1)
		render_img(txt->huds[8], sdl->rend, (t_scale) { 1200, 460, 50, 50 });
	else if (walls->wall[walls->selected_wall].portal == -2 &&
												sects->selected_sector == -1)
		render_img(txt->huds[9], sdl->rend, (t_scale) { 1200, 460, 50, 50 });
}

void	edditing_img_render(t_txt *txt, t_sdl *sdl, t_all_sect *sects,
														t_all_walls *walls)
{
	main_hud_for_edditing(txt, sdl, walls);
	sky(txt, sdl, sects);
	door(txt, sdl, sects);
	window(txt, sdl, walls, sects);
}
