/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_img_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 15:04:47 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/27 15:21:23 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void	render_player_settings(t_txt *txt, t_player *player, t_sdl *sdl)
{
	if (player->pos.x == -1 && player->pos.y == -1)
		return ;
	render_img(txt->huds[15], sdl->rend, (t_scale) { 1000, 260, 200, 50 });
	render_img(txt->huds[20], sdl->rend, (t_scale){ 1000, 310, 200, 50 }); // изменить
	render_img(txt->huds[0], sdl->rend, (t_scale){ 950, 360, 50, 50 });
	render_img(txt->huds[1], sdl->rend, (t_scale){ 1200, 360, 50, 50 });
	render_img(txt->previeww[player->weapon], sdl->rend,
										(t_scale){ 1050, 337, 100, 100 });
	render_img(txt->huds[0], sdl->rend, (t_scale){ 950, 410, 50, 50 });
	render_img(txt->huds[1], sdl->rend, (t_scale){ 1200, 410, 50, 50 });
	/* health */
}

void	object_img_render(t_txt *txt, t_sdl *sdl, t_all_spr_wall *aspr,
													t_all_spr_floor *obj)
{
	render_img(txt->huds[0], sdl->rend, (t_scale) { 950, 10, 50, 50 });
	render_img(txt->huds[1], sdl->rend, (t_scale) { 1200, 10, 50, 50 });
	render_img(txt->huds[17], sdl->rend, (t_scale) { 1000, 7, 200, 50 });
	render_img(txt->huds[0], sdl->rend, (t_scale) { 950, 60, 50, 50 });
	render_img(txt->huds[1], sdl->rend, (t_scale) { 1200, 60, 50, 50 });
	if (obj->select_obj != -1)
		render_img(txt->previewo[obj->obj[obj->select_obj].txt], sdl->rend,
										(t_scale) { 1070, 57, 50, 50 });
	render_img(txt->huds[0], sdl->rend, (t_scale) { 950, 110, 50, 50 });
	render_img(txt->huds[1], sdl->rend, (t_scale) { 1200, 110, 50, 50 });
	render_img(txt->huds[19], sdl->rend, (t_scale) { 1000, 107, 200, 50 });
	render_img(txt->huds[0], sdl->rend, (t_scale) { 950, 160, 50, 50 });
	render_img(txt->huds[1], sdl->rend, (t_scale) { 1200, 160, 50, 50 });
	if (aspr->select_spr != -1)
		render_img(txt->previews[aspr->spr[aspr->select_spr].txt], sdl->rend,
										(t_scale) { 1070, 157, 50, 50 });
	render_img(txt->huds[0], sdl->rend, (t_scale) { 950, 210, 50, 50 });
	render_img(txt->huds[1], sdl->rend, (t_scale) { 1200, 210, 50, 50 });
	render_img(txt->huds[16], sdl->rend, (t_scale) { 1000, 207, 200, 50 });
}
