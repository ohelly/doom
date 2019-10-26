/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_image_on_screen.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 18:32:24 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/26 19:08:30 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void		hud_img_render(t_hud *hud, t_sdl *sdl)
{
	render_img(hud->text_for_app, sdl->rend, (t_scale) { 0, 0, 200, 50 });
	render_img(hud->text_for_app, sdl->rend, (t_scale) { 200, 0, 200, 50 });
}

void		put_image_on_screen(t_doom *doom)
{
	hud_img_render(doom->hud, doom->sdl);
	if (doom->app == 2)
		edditing_img_render(doom->txt, doom->sdl, doom->sects, doom->walls);
	else if (doom->app == 3)
		object_img_render(doom->txt, doom->sdl, doom->aspr);
}
