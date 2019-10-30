/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_editor.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 18:17:38 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/30 17:34:23 by ohelly           ###   ########.fr       */
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
# define DELAY_ERR 50
# define COUNT_T 27
# define COUNT_H 24
# define COUNT_STOBJ 32
# define COUNT_PICS 14
# define COUNT_SKY 4
# define COUNT_SP 6
# define COUNT_OP 16
# define COUNT_WP 3
# define COUNT_FOOT 3
# define COUNT_PIST 12
# define COUNT_SHOTG 8
# define COUNT_RIPPER 7

/*
** POS OF X AND Y
*/

typedef struct			s_v2_vertex
{
	int					x;
	int					y;
}						t_v2;

/*
** STRUCT FOR SCALE IMAGE
*/

typedef struct			s_scale
{
	t_v2				pos;
	int					w;
	int					h;
}						t_scale;

/*
** STRUCT FOR INTERSECT
*/

typedef struct			s_intersect
{
	t_v2				s1;
	t_v2				s2;
	t_v2				hit;
	float				s;
	float				t;
	float				div;
}						t_intersect;

/*
** STRUCT FOR FUNCTION GET_CLOSET_WALL
*/

typedef struct			s_closet_wall
{
	float				dist;
	float				saved_dist;
	t_v2				curr_vertices;
	t_v2				hit;
	t_v2				saved_hit;
}						t_closet;

/*
** SECTORS
*/

typedef struct			s_sectors
{
	int					floor;
	int					ceiling;
	int					txtf;
	int					txtc;
	int					skyb;
	int					door;
	int					light;
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
** WALLS
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
** VERTEX
*/

typedef struct			s_vertex
{
	int					num;
	t_v2				pos;
}						t_vertex;

/*
** Массив строящихся вершин built_v_index[2048];
** num - номер стены на которой лежит проецируемая точка
*/

typedef struct			s_all_vert
{
	int					count;
	int					i;
	int					sel_v;
	t_vertex			list[2048];
	int					built_v_count;
	int					built_v_count_used;
	int					built_v_index[2048];
	t_vertex			projected_v;
	int					cs;
}						t_all_vert;

/*
** POS MOUSE
*/

typedef struct			s_mouse
{
	t_v2				pos;
	t_v2				ppos;
}						t_mouse;

/*
** BRAZENHAM
*/

typedef struct			s_line
{
	t_v2				pos0;
	t_v2				pos1;
	t_v2				d;
}						t_line;

/*
** FILE
*/

typedef struct			s_file
{
	int					fd;
	char				*file_name;
}						t_file;

/*
** STRUCT FOR HUD
*/

typedef struct			s_hud
{
	SDL_Color			color;
	TTF_Font			*font;
	SDL_Surface			*sur;
	SDL_Texture			*text_for_app;
	SDL_Texture			*string;
	char				*msg;
	char				str[3];
}						t_hud;

/*
** SDL POINTER'S
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
** TEXTURES STRUCT
*/

typedef struct			s_txt
{
	SDL_Texture			*wall[COUNT_T];
	SDL_Surface			*swall[COUNT_T];
	SDL_Surface			*stobj[COUNT_STOBJ];
	SDL_Texture			*previews[COUNT_SP];
	SDL_Texture			*previewo[COUNT_OP];
	SDL_Texture			*previeww[COUNT_WP];
	SDL_Texture			*sky[COUNT_SKY];
	SDL_Surface			*ssky[COUNT_SKY];
	SDL_Texture			*huds[COUNT_H];
	SDL_Surface			*foot[COUNT_FOOT];
	SDL_Surface			*pistol[COUNT_PIST];
	SDL_Surface			*shotgun[COUNT_SHOTG];
	SDL_Surface			*ripper[COUNT_RIPPER];
	SDL_Surface			*pics[COUNT_PICS];
	SDL_Surface			*shot;
	int					ind_sky;
}						t_txt;

/*
** SPRITE ON WALL
*/

typedef struct			s_spr_wall
{
	int					wall;
	int					z;
	t_v2				pos;
	int					anim;
	int					frame;
	int					sector;
	int					txt;
}						t_spr_wall;

typedef struct			s_all_spr_wall
{
	int					count;
	int					select_spr;
	t_spr_wall			spr[1000];
}						t_all_spr_wall;

/*
** OBJECT ON FLOOR
*/

typedef struct			s_spr_floor
{
	int					sector;
	t_v2				pos;
	int					anim;
	int					frame;
	int					txt;
}						t_spr_floor;

typedef struct			s_all_spr_floor
{
	int					count;
	int					select_obj;
	t_spr_floor			obj[1000];
}						t_all_spr_floor;

/*
** STRUCT FOR PLAYER
*/

typedef struct			s_player
{
	t_v2				pos;
	int					angle;
	int					sec;
	int					hp;
	int					weapon;
	int					end;
}						t_player;

/*
** STRUCT FOR EXPORT
*/

typedef struct			s_exp
{
	int					wall[COUNT_T];
	int					floor[COUNT_T];
	int					ceil[COUNT_T];
	int					stobj[COUNT_OP];
	int					pics[COUNT_SP];
	int					order[2048];
	int					count;
}						t_export;

/*
** MAIN STRUCT
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
	t_swall				*swall;
	t_hud				*hud;
	t_txt				*txt;
	t_all_spr_wall		*aspr;
	t_all_spr_floor		*obj;
	t_player			*player;
	t_export			*exp;
	int					sh;
	t_v2				map_pos;
	t_v2				move_vector;
}						t_doom;

int						die_msg(char *msg);
void					save(t_doom *doom);
int						sdl_init(t_doom *doom);
void					output(t_doom *doom);
void					key_and_mouse_press(t_doom *doom);
int						get_next_line(const int fd, char **line);
int						line(t_doom *doom, int color);
int						output_pixel(t_doom *doom, t_v2 pos, int color);
int						draw_rectangle(t_doom *doom, t_v2 pos,
												int color, int size);
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
void					build_portal(t_doom *doom, int sw, int aw);
void					find_portal(t_doom *doom);
void					build_sector(t_doom *doom);
int						get_duplicate_wall(t_doom *doom, t_wall w1);
int						split_wall(t_doom *doom);
void					split_sectors(t_doom *doom);
int						remove_built_sector(t_doom *doom);
int						load_img_for_hud(t_hud *hud, t_sdl *sdl, t_txt *txt);
int						load_img_for_txt(t_txt *txt, t_sdl *sdl);
void					put_image_on_screen(t_doom *doom);
void					put_string_on_screen(t_doom *doom);
void					mouse_press(t_doom *doom, t_sdl *sdl, int app);
void					mouse_press_left_two(t_doom *doom, int x, int y);
void					mouse_press_left_thr(t_doom *doom, int x, int y);
void					mouse_press_right(t_doom *doom, int x, int y);
void					my_itoa(char *str, int num);
void					set_sprite_on_wall(t_doom *doom);
int						check_portal(t_doom *doom);
void					set_object(t_doom *doom);
int						num_walls(t_doom *doom, int ver, int sec);
int						check_adjacent_wall(t_doom *doom, int ver1,
													int ver2, int sec);
int						check_portal(t_doom *doom);
int						check_convex(t_doom *doom, int *ind, t_vertex *list);
void					sv(int *a, int *b);
void					sel_sector(int x, int y, t_all_sect *sects,
															t_all_walls *walls);
void					sel_wall(int x, int y, t_all_sect *sects,
															t_all_walls *walls);
void					sel_attr(int x, int y, t_all_sect *sects,
															t_all_walls *walls);
void					sel_floor(int x, int y, t_all_sect *sects);
void					sel_ceiling(int x, int y, t_all_sect *sects);
void					sel_light(int x, int y, t_all_sect *sects);
void					sel_texture_wall(int x, int y, t_all_walls *walls);
void					change_skybox(int x, int y, t_txt *txt);
void					sel_object(int x, int y, t_all_spr_floor *obj,
														t_all_spr_wall *aspr);
void					sel_sprite(int x, int y, t_all_spr_floor *obj,
														t_all_spr_wall *aspr);
void					render_img(SDL_Texture *tex, SDL_Renderer *ren,
																t_scale scale);
void					edditing_img_render(t_txt *txt, t_sdl *sdl,
										t_all_sect *sects, t_all_walls *walls);
void					main_hud_for_edditing(t_txt *txt, t_sdl *sdl,
										t_all_walls *walls, t_all_sect *sects);
void					object_img_render(t_txt *txt, t_sdl *sdl,
									t_all_spr_wall *aspr, t_all_spr_floor *obj);
void					draw_sprite(t_doom *doom, int color);
void					draw_building_line(t_doom *doom, int color);
void					draw_sector(t_doom *doom, int sector, int color);
void					draw_wall(t_doom *doom, t_wall wall, int color);
int						draw_rectangle(t_doom *doom, t_v2 pos, int color,
																	int size);
int						check_sprite(t_doom *doom, int sw, int aw);
void					correction_height_sprite(t_doom *doom);
void					height_spr(int x, int y, t_all_spr_wall *aspr,
													t_all_sect *sectors);
int						lines_intersect_loop(t_doom *doom, t_v2 p1, t_v2 p2);
int						scalar_product(t_v2 v1, t_v2 v2, t_v2 v3);
void					export_vert(t_doom *doom);
int						sorted_vert(t_doom *doom, int index);
int						count_wall(t_doom *doom, int ind);
void					export_sector(t_doom *doom);
int						check_rotation(t_doom *doom, int ind, t_vertex *list);
void					output_wall(t_doom *doom, int count, int ind);
void					output_wall_rev(t_doom *doom, int count, int ind);
void					sel_txtc(int x, int y, t_all_sect *sects);
void					sel_txtf(int x, int y, t_all_sect *sects);
int						init_preview(t_doom *doom);
void					sel_txt_spr(int x, int y, t_all_spr_wall *aspr);
void					sel_txt_obj(int x, int y, t_all_spr_floor *obj);
void					set_player(t_doom *doom);
void					draw_player(t_doom *doom, int color);
void					set_end_player(t_doom *doom);
void					render_player_settings(t_txt *txt, t_player *player,
																t_sdl *sdl);
void					set_weapon(int x, int y, t_player *player);
void					export_all_texture(t_doom *doom);
void					export_wall_tx(t_doom *doom);
int						load_txt_to_surface(t_txt *txt);
void					export_ceil_tx(t_doom *doom);
void					export_floor_tx(t_doom *doom);
int						load_surface(t_doom *doom);
void					export_sky_tx(t_doom *doom);
void					export_shot_tx(t_doom *doom);
void					export_weapon_data(t_doom *doom);
void					out_img_weapon(SDL_Surface *sur, t_file *file);
int						load_weapon(t_doom *doom);
void					export_stobj_data(t_doom *doom);
int						load_st_obj(t_doom *doom);
int						load_pickobj(t_doom *doom);
void					output_text_stobj(int ind, t_doom *doom);
void					export_pics(t_doom *doom);
int						load_pics(t_doom *doom);
void					export_attr(t_doom *doom, int ind);
void					export_objs(t_doom *doom);
void					export_pospics(t_doom *doom);
void					export_player(t_doom *doom);
void					health_player(int x, int y, t_player *player);
void					load_sector(t_doom *doom, char *line);
void					load_obj(t_doom *doom, char *line);
void					load_spr(t_doom *doom, char *line);
void					import_player(t_doom *doom, char *line);
int						load_sky(t_txt *txt, t_sdl *sdl);

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
