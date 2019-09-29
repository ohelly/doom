/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadtextures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 14:53:36 by dtoy              #+#    #+#             */
/*   Updated: 2019/09/29 19:59:30 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		loadtextureobjs(t_doom *doom, t_obj *obj, t_player player)
{
	SDL_Surface *surface;
	
	obj[0].img.data = (int**)ft_memalloc(sizeof(int*) * obj[0].cnt_frms);
	surface = IMG_Load("textures/obj/bar/BAR1A0.png");
	obj[0].img.data[0] = (int*)surface->pixels;
	surface = IMG_Load("textures/obj/bar/BAR1B0.png");
	obj[0].img.data[1] = (int*)surface->pixels;
	surface = IMG_Load("textures/obj/bar/BAR1C0.png");
	obj[0].img.data[2] = (int*)surface->pixels;
	surface = IMG_Load("textures/obj/bar/BAR1D0.png");
	obj[0].img.data[3] = (int*)surface->pixels;
	surface = IMG_Load("textures/obj/bar/BAR1E0.png");
	obj[0].img.data[4] = (int*)surface->pixels;
	surface = IMG_Load("textures/obj/bar/BAR1F0.png");
	obj[0].img.data[5] = (int*)surface->pixels;
	surface = IMG_Load("textures/obj/bar/BAR1G0.png");
	obj[0].img.data[6] = (int*)surface->pixels;
	surface = IMG_Load("textures/obj/bar/BAR1H0.png");
	obj[0].img.data[7] = (int*)surface->pixels;
	surface = IMG_Load("textures/obj/bar/BAR1I0.png");
	obj[0].img.data[8] = (int*)surface->pixels;
	surface = IMG_Load("textures/obj/bar/BAR1J0.png");
	obj[0].img.data[9] = (int*)surface->pixels;
	surface = IMG_Load("textures/obj/bar/BAR1K0.png");
	obj[0].img.data[10] = (int*)surface->pixels;
	surface = IMG_Load("textures/obj/bar/BAR1L0.png");
	obj[0].img.data[11] = (int*)surface->pixels;
	surface = IMG_Load("textures/obj/bar/BAR1M0.png");
	obj[0].img.data[12] = (int*)surface->pixels;
	obj[0].img.w = surface->w;
	obj[0].img.h = surface->h;

	obj[1].img.data = (int**)ft_memalloc(sizeof(int*) * obj[1].cnt_frms);
	surface = IMG_Load("textures/obj/people/devka/devka.png");
	obj[1].img.data[0] = (int*)surface->pixels;
	surface = IMG_Load("textures/obj/people/devka/devka1.png");
	obj[1].img.data[1] = (int*)surface->pixels;
	obj[1].img.w = surface->w;
	obj[1].img.h = surface->h;

	obj[2].img.data = (int**)ft_memalloc(sizeof(int*) * obj[2].cnt_frms);
	surface = IMG_Load("textures/obj/head/HEADA1.png");
	obj[2].img.data[0] = (int*)surface->pixels;
	surface = IMG_Load("textures/obj/head/HEADB1.png");
	obj[2].img.data[1] = (int*)surface->pixels;
	surface = IMG_Load("textures/obj/head/HEADC1.png");
	obj[2].img.data[2] = (int*)surface->pixels;
	surface = IMG_Load("textures/obj/head/HEADD1.png");
	obj[2].img.data[3] = (int*)surface->pixels;
	surface = IMG_Load("textures/obj/head/HEADE1.png");
	obj[2].img.data[4] = (int*)surface->pixels;
	surface = IMG_Load("textures/obj/head/HEADF1.png");
	obj[2].img.data[5] = (int*)surface->pixels;
	obj[2].img.w = surface->w;
	obj[2].img.h = surface->h;

	obj[3].img.data = (int**)ft_memalloc(sizeof(int*) * obj[3].cnt_frms);
	surface = IMG_Load("textures/obj/people/svidetel/svidetel.png");
	obj[3].img.data[0] = (int*)surface->pixels;
	obj[3].img.w = surface->w;
	obj[3].img.h = surface->h;
	return (0);
}

int		loadtextures(t_doom *doom)
{
	loadtextureobjs(doom, doom->obj, doom->player);
	return (0);
}
