/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:19:34 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/17 17:23:09 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

/*
** Рендерит изображение и задает ей координаты с размером,
** которые хранятся в scale
*/

void		render_img(SDL_Texture *tex, SDL_Renderer *ren, t_scale scale)
{
	SDL_Rect	dst;

	dst.x = scale.pos.x;
	dst.y = scale.pos.y;
	dst.w = scale.w;
	dst.h = scale.h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}