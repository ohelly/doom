/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_hud_for_edditing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 14:28:33 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/29 02:43:19 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void	sky_sect_ceil(t_txt *txt, t_sdl *sdl)
{
	render_img(txt->huds[0], sdl->rend, (t_scale) { { 650, 10 }, 50, 50 });
	render_img(txt->huds[1], sdl->rend, (t_scale) { { 900, 10 }, 50, 50 });
	render_img(txt->huds[7], sdl->rend, (t_scale) { { 700, 7 }, 200, 50 });
	/* текстурка на скайбокс */
	render_img(txt->huds[0], sdl->rend, (t_scale) { { 950, 10 }, 50, 50 });
	render_img(txt->huds[1], sdl->rend, (t_scale) { { 1200, 10 }, 50, 50 });
	render_img(txt->huds[2], sdl->rend, (t_scale) { { 1000, 7 }, 200, 50 });
	render_img(txt->huds[0], sdl->rend, (t_scale) { { 950, 110 }, 50, 50 });
	render_img(txt->huds[1], sdl->rend, (t_scale) { { 1200, 110 }, 50, 50 });
	render_img(txt->huds[3], sdl->rend, (t_scale) { { 1000, 107 }, 200, 50 });
}

void	floor_text_ceiltext(t_txt *txt, t_sdl *sdl, t_all_sect *sects)
{
	render_img(txt->huds[0], sdl->rend, (t_scale) { { 950, 60 }, 50, 50 });
	render_img(txt->huds[1], sdl->rend, (t_scale) { { 1200, 60 }, 50, 50 });
	render_img(txt->huds[4], sdl->rend, (t_scale) { { 1000, 57 }, 200, 50 });
	render_img(txt->huds[0], sdl->rend, (t_scale) { { 950, 210 }, 50, 50 });
	render_img(txt->huds[1], sdl->rend, (t_scale) { { 1200, 210 }, 50, 50 });
	render_img(txt->huds[5], sdl->rend, (t_scale) { { 1000, 157 }, 200, 50 });
	if (sects->selected_sector != -1)
		render_img(txt->wall[sects->sectors[sects->selected_sector].txtf],
		sdl->rend, (t_scale) { { 1070, 207 }, 60, 50 });
	render_img(txt->huds[0], sdl->rend, (t_scale) { { 950, 310 }, 50, 50 });
	render_img(txt->huds[1], sdl->rend, (t_scale) { { 1200, 310 }, 50, 50 });
	render_img(txt->huds[6], sdl->rend, (t_scale) { { 1000, 257 }, 200, 50 });
	if (sects->selected_sector != -1)
		render_img(txt->wall[sects->sectors[sects->selected_sector].txtc],
		sdl->rend, (t_scale) { { 1070, 307 }, 60, 50 });
}

void	main_hud_for_edditing(t_txt *txt, t_sdl *sdl, t_all_walls *walls,
													t_all_sect *sects)
{
	sky_sect_ceil(txt, sdl);
	floor_text_ceiltext(txt, sdl, sects);
	render_img(txt->huds[0], sdl->rend, (t_scale) { { 950, 510 }, 50, 50 });
	render_img(txt->huds[1], sdl->rend, (t_scale) { { 1200, 510 }, 50, 50 });
	render_img(txt->huds[11], sdl->rend, (t_scale) { { 1000, 507 }, 200, 50 });
	render_img(txt->huds[0], sdl->rend, (t_scale) { { 950, 560 }, 50, 50 });
	render_img(txt->huds[1], sdl->rend, (t_scale) { { 1200, 560 }, 50, 50 });
	render_img(txt->huds[12], sdl->rend, (t_scale) { { 1000, 557 }, 200, 50 });
	render_img(txt->huds[0], sdl->rend, (t_scale) { { 950, 660 }, 50, 50 });
	render_img(txt->huds[1], sdl->rend, (t_scale) { { 1200, 660 }, 50, 50 });
	render_img(txt->huds[13], sdl->rend, (t_scale) { { 1000, 607 }, 200, 50 });
	if (walls->selected_wall != -1)
		render_img(txt->wall[walls->wall[walls->selected_wall].txt],
							sdl->rend, (t_scale) { { 1070, 657 }, 60, 50 });
}
