/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_img_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 15:04:47 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/26 19:14:27 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void	object_img_render(t_txt *txt, t_sdl *sdl, t_all_spr_wall *aspr)
{
	// < object >
	render_img(txt->huds[0], sdl->rend, (t_scale) { 950, 10, 50, 50 });
	render_img(txt->huds[1], sdl->rend, (t_scale) { 1200, 10, 50, 50 });
	render_img(txt->huds[17], sdl->rend, (t_scale) { 1000, 7, 200, 50 });
	// < texture obj >
	render_img(txt->huds[0], sdl->rend, (t_scale) { 950, 60, 50, 50 });
	render_img(txt->huds[1], sdl->rend, (t_scale) { 1200, 60, 50, 50 });
	/* Текстура объекта */
	render_img(txt->huds[0], sdl->rend, (t_scale) { 950, 110, 50, 50 });
	render_img(txt->huds[1], sdl->rend, (t_scale) { 1200, 110, 50, 50 });
	render_img(txt->huds[19], sdl->rend, (t_scale) { 1000, 107, 200, 50 });
	// < texture sprite >
	render_img(txt->huds[0], sdl->rend, (t_scale) { 950, 160, 50, 50 });
	render_img(txt->huds[1], sdl->rend, (t_scale) { 1200, 160, 50, 50 });
	render_img(txt->previews[aspr->spr[aspr->select_spr].txt], sdl->rend,
										(t_scale) { 1070, 157, 50, 50 });
	// < height = >
	render_img(txt->huds[0], sdl->rend, (t_scale) { 950, 210, 50, 50 });
	render_img(txt->huds[1], sdl->rend, (t_scale) { 1200, 210, 50, 50 });
	render_img(txt->huds[16], sdl->rend, (t_scale) { 1000, 207, 200, 50 });
}
