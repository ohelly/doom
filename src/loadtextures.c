/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadtextures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 14:53:36 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/01 20:02:54 by dtoy             ###   ########.fr       */
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

	//doom->txt[0].data = (int**)ft_memalloc(sizeof(int*) * 1);
	surface = IMG_Load("textures/walls/WALL3.png");
	doom->txt[0].data = (int*)surface->pixels;
	doom->txt[0].w = surface->w;
	doom->txt[0].h = surface->h;
	return (0);
}

int		findvx(t_xy *v1, t_xy *v2, t_xy *vert, int wall)
{
	v1->x = vert[wall].x;
	v1->y = vert[wall].y;
	v2->x = vert[wall + 1].x;
	v2->y = vert[wall + 1].y;
	return (0);
}

int		findpicpoints(t_doom *doom, t_pic *pic)
{
	t_xy	d1;
	t_xy	d2;
	t_xy	v1;
	t_xy	v2;
	float	dist1;
	float	dist2;
	float	hw = 3;
	
	findvx(&v1, &v2, doom->sector[pic->sector].vert, pic->wall);
	d1.x = v1.x - pic->p.x;
	d1.y = v1.y - pic->p.y;
	d2.x = pic->p.x - v2.x;
	d2.y = pic->p.y - v2.y;
	
	//printf("t1.x - %f, t2.x - %f\n", t1.x, t2.x);
	//printf("t1.z - %f, t2.z - %f\n", t1.z, t2.z);
	dist1 = sqrtf(powf(d1.x, 2) + powf(d1.y, 2));
	dist2 = sqrtf(powf(d2.x, 2) + powf(d2.y, 2));
	printf("dist1 - %f, dist2 - %f\n", dist1, dist2);
	pic->p1.x = pic->p.x - ((hw * (pic->p.x - v1.x)) / dist1);
	pic->p1.y = pic->p.y - ((hw * (pic->p.y - v1.y)) / dist1);
	pic->p2.x = pic->p.x - ((hw * (pic->p.x - v2.x)) / dist2);
	pic->p2.y = pic->p.y - ((hw * (pic->p.y - v2.y)) / dist2);
	printf("p1.x - %f, p2.x - %f\n", pic->p1.x, pic->p2.x);
	printf("p1.z - %f, p2.z - %f\n", pic->p1.y, pic->p2.y);

	return (0);
}

int		loadtexturepics(t_doom *doom, t_pic *pic)
{
	SDL_Surface *surface;
	
	pic[0].img.data = (int**)ft_memalloc(sizeof(int*) * pic[0].cnt_frms);
	surface = IMG_Load("textures/pic/pepe.png");
	pic[0].img.data[0] = (int*)surface->pixels;
	pic[0].img.w = surface->w;
	pic[0].img.h = surface->h;
	findpicpoints(doom, &pic[0]);
	return (0);
}

int		loadtextures(t_doom *doom)
{
	loadtextureobjs(doom, doom->obj, doom->player);
	loadtexturepics(doom, doom->pic);
	return (0);
}
