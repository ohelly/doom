/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadtextures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 14:53:36 by dtoy              #+#    #+#             */
/*   Updated: 2019/09/29 17:13:03 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		loadtextureobjs(t_doom *doom, t_obj *obj, t_player player)
{
	SDL_Surface *surface;
	surface = IMG_Load("textures/obj/people/svidetel/svidetel.png");
	obj[0].img.data = (int**)ft_memalloc(sizeof(int*) * obj->cnt_frms);
	obj[0].img.data[0] = (int*)surface->pixels;
	obj[0].img.w = surface->w;
	obj[0].img.h = surface->h;
	surface = IMG_Load("textures/obj/people/devka/devka.png");
	obj[1].img.data = (int**)ft_memalloc(sizeof(int*) * obj->cnt_frms);
	obj[1].img.data[0] = (int*)surface->pixels;
	obj[1].img.w = surface->w;
	obj[1].img.h = surface->h;
	return (0);
}

int		loadtextures(t_doom *doom)
{
	loadtextureobjs(doom, doom->obj, doom->player);
	return (0);
}
