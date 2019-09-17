/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 18:17:38 by dtoy              #+#    #+#             */
/*   Updated: 2019/09/12 16:47:35 by ohelly           ###   ########.fr       */
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

/*
	POS OF X AND Y
					*/

typedef struct			s_v2_vertex
{
	int					x;
	int					y;
}						t_v2;

/*
	SECTORS
			*/

typedef struct			s_sectors
{
	
}						t_sectors;

typedef struct			s_all_sect
{ 
	int					count;
	int					i;
	t_sectors			sectors[2048];
	int					selected_sector;
}						t_all_sect;

/*
	WALLS
			*/

typedef struct			s_wall
{
	int					sectors;
	int					vert_one;
	int					vert_two;
	int					portal;
}						t_wall;

typedef struct			s_all_walls
{
	int					count;
	int					i;
	t_wall				wall[2048];
}						t_all_walls;

/*
	VERTEX
			*/

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
	int					built_v_count;
	//Массив строящихся вершин
	int					built_v_index[2048];
	t_v2				projected_v;
}						t_all_vert;

/*
	POS MOUSE
				*/

typedef struct			s_mouse
{
	t_v2				pos;
	t_v2				ppos;
}						t_mouse;

/*
	BRAZENHAM
				*/

typedef struct			s_line
{
	t_v2				pos0;
	t_v2				pos1;
	t_v2				d;
}						t_line;

/*
	FILE
			*/

typedef struct			s_file
{
	int					fd;
	char				*file_name;
}						t_file;

/*
	SDL POINTER'S
					*/

typedef struct			s_sdl
{
	SDL_Window			*win;
	SDL_Renderer		*rend;
	SDL_Texture			*tex;
	int					*pix;
	SDL_Event			ev;
}						t_sdl;

/*
	MAIN STRUCT
				*/

typedef struct			s_doom
{
	int					app;
	t_sdl				*sdl;
	t_line				*line;
	t_mouse				*mouse;
	t_all_vert			*verts;
	t_all_sect			*sects;
	t_all_walls			*walls;
	t_file				*file;
	char				*save_name;
	int					sh;
	t_v2				map_pos;
	t_v2				move_vector;
}						t_doom;

int						save(t_doom *doom);
void					output(t_doom *doom);
void					key_and_mouse_press(t_doom *doom);
int						get_next_line(const int fd, char **line);
int						line(t_doom *doom, int color);
int						output_pixel(t_doom *doom, t_v2 pos, int color);
int						draw_rectangle(t_doom *doom, t_v2 pos, int color, int size);
void					put_canvas(t_doom *doom);
void					put_select(t_doom *doom, t_mouse *mouse);
float					line_distance(t_v2 l1, t_v2 l2, t_v2 p, t_v2 *hit);
void					get_closest_sector(t_doom *doom);
int						get_closest_wall(t_doom *doom);
int						lines_intersect_loop(t_doom *doom, t_v2 p1, t_v2 p2);
int						vertex_is_free(t_doom *doom, t_v2 v);
int						load_map(char *av, t_doom *doom);
int						move_map(t_doom *doom);
int						vertices_return_map_pos(t_doom *doom);

/*
**	Math
*/

t_v2					v2_add(t_v2 v1, t_v2 v2);
int						v2_compare(t_v2 v1, t_v2 v2);
int						v2_in_borders(t_v2 v2, int maxx, int maxy);
double					min(double a, double b);
double					max(double a, double b);
double					clamp(double a, double mi, double ma);


#endif