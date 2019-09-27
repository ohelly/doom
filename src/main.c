/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:10:02 by dtoy              #+#    #+#             */
/*   Updated: 2019/09/26 19:07:31 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"


int     loaddata(t_textures *textures, char *str, int s,  int i)
{
    SDL_Surface	*sur;
    sur = IMG_Load(str);
    textures->spr_data[s].data[i] = (int*)sur->pixels;
    textures->spr_data[s].w[i] = sur->w;
    textures->spr_data[s].h[i] = sur->h;
    return (0);
}

int     loadwalls(t_textures *textures)
{
    SDL_Surface	*sur;

    sur = IMG_Load("textures/W104_1.png");
    textures->walls[0].data = (int*)sur->pixels;
    textures->walls[0].w = sur->w;
    textures->walls[0].h = sur->h;
    printf("w - %d\n", sur->w);
    printf("h - %d\n", sur->h);
    return (0);
}

int     loadtexture(t_doom *doom)
{
	SDL_Surface	*s;
    int         *t;
    int         i = 0;
   // printf("NOOOOOOO\n");
    //doom->textures->sprites = ft_memalloc(sizeof(SDL_Surface*) * doom->numsprites);
    doom->textures->spr_data = (t_data*)ft_memalloc(sizeof(t_data) * doom->numsprites);
    doom->textures->walls = (t_walls*)ft_memalloc(sizeof(t_walls) * 1);
    //printf("spr - %d\n", doom->numsprites);
    while (i < 6)
        loaddata(doom->textures, "textures/svidetel2.bmp", 0, i++);
    i = 0;
	while (i < 6)
        loaddata(doom->textures, "textures/muzhik.png", 2, i++);
    loaddata(doom->textures, "textures/HEADA1.png", 1, 0);
    loaddata(doom->textures, "textures/HEADB1.png", 1, 1);
    loaddata(doom->textures, "textures/HEADC1.png", 1, 2);
    loaddata(doom->textures, "textures/HEADD1.png", 1, 3);
    loaddata(doom->textures, "textures/HEADE1.png", 1, 4);
    loaddata(doom->textures, "textures/HEADF1.png", 1, 5);

	loaddata(doom->textures, "textures/devka.png", 3, 0);
    loaddata(doom->textures, "textures/devka.png", 3, 1);
    loaddata(doom->textures, "textures/devka.png", 3, 2);
    loaddata(doom->textures, "textures/devka1.png", 3, 3);
    loaddata(doom->textures, "textures/devka1.png", 3, 4);
    loaddata(doom->textures, "textures/devka1.png", 3, 5);
/*	s =  IMG_Load("textures/svidetel2.bmp");
    //printf("NOOOOOOO\n");
    doom->textures->spr_data[0].data = (int*)s->pixels;
	doom->textures->spr_data[0].w = s->w;
    doom->textures->spr_data[0].h = s->h;
    loadsprite();
    s = IMG_Load("textures/HEADD1.png");
	doom->textures->spr_data[1].data = (int*)s->pixels;
    doom->textures->spr_data[1].w = s->w;
    doom->textures->spr_data[1].h = s->h;*/
    //printf("NOOOOOOO\n");*/
    loadwalls(doom->textures);
    return (0);
}
int     main()
{
    t_doom  *doom;

    if (!(doom = (t_doom*)ft_memalloc(sizeof(t_doom))))
        return (0);
    init_all(doom);
    loadmap(doom);
    loadtexture(doom);
    loadgame(doom);
    
  //  loadtexture(doom);
    return (0);
}
