/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 18:17:38 by dtoy              #+#    #+#             */
/*   Updated: 2019/09/04 16:37:16 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H
# include "libft.h"
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <SDL.h>
# include "get_next_line.h"
# define WIDTH 1280
# define HEIGHT 720
# define BUFF_SIZE 1

typedef struct			s_sectors
{
	int					start;
	int					end;
}						t_sectors;

typedef struct			s_all_sect
{ 
	int					count;
	int					i;
	t_sectors			sectors[2048];
}						t_all_sect;

typedef struct			s_v2_vertex
{
	int					x;
	int					y;
}						t_v2;

typedef struct			s_vertex
{
	int					num;
	t_v2				pos;
}						t_vertex;

typedef struct			s_all_vert
{ 
	int					count;
	int					i;
	int					sel_v;
	t_vertex			list[2048];
}						t_all_vert;

typedef struct			s_mouse
{
	t_v2				pos;
	t_v2				ppos;
}						t_mouse;

typedef struct			s_line
{
	t_v2				pos0;
	t_v2				pos1;
	t_v2				d;
}						t_line;

typedef struct			s_sdl
{
	SDL_Window			*win;
	SDL_Renderer		*rend;
	SDL_Texture			*tex;
	int					*pix;
	SDL_Event			ev;
}						t_sdl;

typedef struct			s_doom
{
	int					app;
	t_sdl				*sdl;
	t_line				*line;
	t_mouse				*mouse;
	t_all_vert			*verts;
	t_all_sect			*sects;
	int					mov_x;
	int					mov_y;
	int					sh;
}						t_doom;

void					output(t_doom *doom);
void					key_and_mouse_press(t_doom *doom);
int						get_next_line(const int fd, char **line);
int						line(t_doom *doom, int color);
int						output_pixel(t_doom *doom, int pos, int color);
int						draw_rectangle(t_doom *doom, t_v2 pos, int color, int size);
void					put_canvas(t_doom *doom);
void					put_select(t_doom *doom, t_mouse *mouse);
float					line_distance(t_v2 l1, t_v2 l2, t_v2 p, t_v2 *hit);

/*
**	Math
*/

t_v2					v2_add(t_v2 v1, t_v2 v2);
double					min(double a, double b);
double					max(double a, double b);
double					clamp(double a, double mi, double ma);


#endif