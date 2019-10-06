/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_editor.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 18:17:38 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/06 16:12:25 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_EDITOR_H
# define DOOM_EDITOR_H
# include "libft.h"
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <SDL.h>
# include "SDL_image.h"
# include "SDL_ttf.h"
# include "get_next_line.h"
# define WIDTH 1280
# define HEIGHT 720
# define BUFF_SIZE 1
# define DELAY_ERR 50
# define COUNT_W 21
# define COUNT_F 21
# define COUNT_HS 10
# define COUNT_HO 21
# define COUNT_O 21

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
	int					floor;
	int					ceiling;
	int					txtf;
	int					txtc;
	int					skyb;
	int					door;
	float				light;
}						t_sectors;

typedef struct			s_all_sect
{ 
	int					count;
	int					i;
	t_sectors			sectors[2048];
	int					selected_sector;
}						t_all_sect;

typedef struct			s_swall
{
	int					v1;
	int					v2;
	int					wall1;
	int					wall2;
	int					sec;
}						t_swall;

/*
	WALLS
			*/

typedef struct			s_wall
{
	int					sectors;
	int					vert_one;
	int					vert_two;
	int					portal;
	int					txt;
}						t_wall;

typedef struct			s_all_walls
{
	int					count;
	int					i;
	t_wall				wall[2048];
	int					selected_wall;
	int					adjacent_wall;
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
	int					built_v_count_used;
	//Массив строящихся вершин
	int					built_v_index[2048];
	//num - номер стены на которой лежит проецируемая точка
	t_vertex			projected_v;
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
	STRUCT FOR HUD
					*/

typedef struct			s_hud
{
	SDL_Color			color;
	TTF_Font			*font;
	SDL_Surface			*sur;
	SDL_Texture			*text_for_app;
	SDL_Texture			*string;
	char				*msg;
}						t_hud;

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
	TEXTURES STRUCT
					*/

typedef struct			s_txt
{
	SDL_Texture			*wall[21];
	SDL_Texture			*floor[21];
	SDL_Texture			*obj[21];
	SDL_Texture			*huds[COUNT_HS];
	SDL_Texture			*hudo[21];
}						t_txt;

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
	t_swall				*swall;
	t_hud				*hud;
	t_txt				*txt;
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
void					build_portal(t_doom *doom);
void					find_portal(t_doom *doom);
void					build_sector(t_doom *doom);
int						get_duplicate_wall(t_doom *doom, t_wall w1);
int						split_wall(t_doom *doom);
void					split_sectors(t_doom *doom);
int						remove_built_sector(t_doom *doom);
int						load_img_for_hud(t_doom *doom);
void					put_image_on_screen(t_doom *doom);
void					put_string_on_screen(t_doom *doom);
void					edit_sector(t_doom *doom);
void					mouse_press(t_doom *doom, int x, int y);

/*
**	Math
*/

t_v2					v2_add(t_v2 v1, t_v2 v2);
int						v2_compare(t_v2 v1, t_v2 v2);
int						v2_in_borders(t_v2 v2, int maxx, int maxy);
double					min(double a, double b);
double					max(double a, double b);
double					clamp(double a, double mi, double ma);
float					distance(t_v2 p1, t_v2 p2);

#endif