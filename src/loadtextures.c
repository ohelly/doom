/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadtextures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 14:53:36 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/03 20:18:59 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		new_image(t_doom *doom, char *texture_name)
{
	t_img		img;
	SDL_Surface	*surface;

	surface = IMG_Load(texture_name);
	img.data = (int*)surface->pixels;
	img.w = surface->w;
	img.h = surface->h;
	
	doom->images[doom->images_count] = img;
	doom->images_count++;
	printf("Image %s loaded.\n", texture_name);
	return (doom->images_count - 1);
}

int		loadtextureobjs(t_doom *doom, t_obj *obj, t_player player)
{
	SDL_Surface *surface;
	int a;

	//	N NE E SE S SW W WN

	obj[0].images[0][0] = new_image(doom, "textures/obj/head2/headN.png");
	obj[0].images[1][0] = new_image(doom, "textures/obj/head2/headNE.png");
	obj[0].images[2][0] = new_image(doom, "textures/obj/head2/headE.png");
	obj[0].images[3][0] = new_image(doom, "textures/obj/head2/headSE.png");
	obj[0].images[4][0] = new_image(doom, "textures/obj/head2/headS.png");
	obj[0].images[5][0] = new_image(doom, "textures/obj/head2/headSW.png");
	obj[0].images[6][0] = new_image(doom, "textures/obj/head2/headW.png");
	obj[0].images[7][0] = new_image(doom, "textures/obj/head2/headNW.png");
	obj[0].images[8][0] = new_image(doom, "textures/obj/head2/headDead.png");
	doom->enemy = create_enemy(doom, &obj[0]);
	printf("ok\n");
	/*
	obj[0].images[0][0] = new_image(doom, "textures/obj/bar/BAR1A0.png");
	obj[0].images[0][1] = new_image(doom, "textures/obj/bar/BAR1B0.png");
	obj[0].images[0][2] = new_image(doom, "textures/obj/bar/BAR1C0.png");
	obj[0].images[0][3] = new_image(doom, "textures/obj/bar/BAR1D0.png");
	obj[0].images[0][4] = new_image(doom, "textures/obj/bar/BAR1E0.png");
	obj[0].images[0][5] = new_image(doom, "textures/obj/bar/BAR1F0.png");
	obj[0].images[0][6] = new_image(doom, "textures/obj/bar/BAR1G0.png");
	obj[0].images[0][7] = new_image(doom, "textures/obj/bar/BAR1H0.png");
	obj[0].images[0][8] = new_image(doom, "textures/obj/bar/BAR1I0.png");
	obj[0].images[0][9] = new_image(doom, "textures/obj/bar/BAR1J0.png");
	obj[0].images[0][10] = new_image(doom, "textures/obj/bar/BAR1K0.png");
	obj[0].images[0][11] = new_image(doom, "textures/obj/bar/BAR1L0.png");
	obj[0].images[0][12] = new_image(doom, "textures/obj/bar/BAR1M0.png");

	doom->enemy = create_enemy(doom, &obj[0]);
	a = new_image(doom, "textures/obj/head/HEADA1.png");
	obj[0].images[1][0] = a;
	obj[0].images[2][0] = a;
	obj[0].images[3][0] = a;
	obj[0].images[4][0] = a;
	obj[0].images[5][0] = a;
	obj[0].images[6][0] = a;
	obj[0].images[7][0] = a;
	*/
	obj[1].images[0][0] = new_image(doom, "textures/obj/people/devka/devka.png");
	obj[1].images[0][1] = new_image(doom, "textures/obj/people/devka/devka1.png");

	obj[2].images[0][0] = new_image(doom, "textures/obj/head/HEADA1.png");
	obj[2].images[0][1] = new_image(doom, "textures/obj/head/HEADB1.png");
	obj[2].images[0][2] = new_image(doom, "textures/obj/head/HEADC1.png");
	obj[2].images[0][3] = new_image(doom, "textures/obj/head/HEADD1.png");
	obj[2].images[0][4] = new_image(doom, "textures/obj/head/HEADE1.png");
	obj[2].images[0][5] = new_image(doom, "textures/obj/head/HEADF1.png");

	obj[3].images[0][0] = new_image(doom, "textures/obj/people/svidetel/svidetel.png");
	//doom->txt[0].data = (int**)ft_memalloc(sizeof(int*) * 1);

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
	
	
	//pic[0].img.data = (int**)ft_memalloc(sizeof(int*) * pic[0].cnt_frms);
	//surface = IMG_Load("textures/pic/pepe.png");
	//pic[0].img.data[0] = (int*)surface->pixels;
	//pic[0].img.w = surface->w;
	//pic[0].img.h = surface->h;
	//findpicpoints(doom, &pic[0]);
	return (0);
}

int		loadimage(t_img *img, char *str)
{
	SDL_Surface *surface;

	surface = IMG_Load(str);
	img->data = (int*)surface->pixels;
	img->w = surface->w;
	img->h = surface->h;
	return (0);
}

int		loadtexturewalls(t_doom *doom, t_texture *txt)
{
	txt->img = (t_img*)ft_memalloc(sizeof(t_img) * 5);
	loadimage(&txt->img[0], "textures/walls/1.png");
	loadimage(&txt->img[1], "textures/walls/2.png");
	loadimage(&txt->img[2], "textures/walls/3.png");
	loadimage(&txt->img[3], "textures/walls/4.png");
	loadimage(&txt->img[4], "textures/walls/5.png");

	return (0);
}

int		loadtextures(t_doom *doom)
{
	loadtextureobjs(doom, doom->obj, doom->player);
	loadtexturewalls(doom, doom->txt);
	//loadtexturepics(doom, doom->pic);
	printf("ok\n");
	return (0);
}
