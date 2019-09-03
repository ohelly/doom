/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 18:17:38 by dtoy              #+#    #+#             */
/*   Updated: 2019/09/03 17:15:51 by ohelly           ###   ########.fr       */
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

typedef struct			s_vertex
{
	int					num;
	int					x;
	int					y;
}						t_vertex;

typedef struct			s_all_vert
{ 
	int					count;
	int					sel_v;
	int					i;
	t_vertex			list[2048];
}						t_all_vert;

typedef struct			s_mouse
{
	int					x;
	int					y;
	int					ppos_x;
	int					ppos_y;
}						t_mouse;

typedef struct			s_line
{
	int					x0;
	int					y0;
	int					x1;
	int					y1;
	int					dx;
	int					dy;
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
	int					sh;
}						t_doom;

void					output(t_doom *doom);
void					key_and_mouse_press(t_doom *doom);
int						get_next_line(const int fd, char **line);
int						line(t_doom *doom, int color);
int						output_pixel(t_doom *doom, int pos, int color);
int						draw_rectangle(t_doom *doom, int x, int y, int color, int size);
void					put_canvas(t_doom *doom);
void					put_select(t_doom *doom, t_mouse *mouse);


#endif