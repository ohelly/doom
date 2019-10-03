/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 19:45:10 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/03 16:09:33 by dtoy             ###   ########.fr       */
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
# include <SDL_image.h>
# include <get_next_line.h>

# define WIDTH 1920
# define HEIGHT 1080
# define NEARZ 1e-4f
# define FARZ 5
# define NEARSIDE 1e-5f
# define FARSIDE 20.f
# define EyeHeight  15
# define DuckHeight 2.5
# define HeadMargin 1
# define KneeHeight 2
# define HFOV (1.0 * 0.73f * HEIGHT / WIDTH)
# define VFOV (1.0 * .2f)
# define min(a,b)             (((a) < (b)) ? (a) : (b))
# define max(a,b)             (((a) > (b)) ? (a) : (b))
# define clamp(a, mi,ma)      min(max(a,mi),ma)
//# define VXS(x0,y0, x1,y1)    ((x0)*(y1) - (x1)*(y0))
# define Overlap(a0,a1,b0,b1) (min(a0,a1) <= max(b0,b1) && min(b0,b1) <= max(a0,a1))
# define IntersectBox(x0,y0, x1,y1, x2,y2, x3,y3) (Overlap(x0,x1,x2,x3) && Overlap(y0,y1,y2,y3))
# define PointSide(px,py, x0,y0, x1,y1) vxs((x1)-(x0), (y1)-(y0), (px)-(x0), (py)-(y0))
//# define Intersect(x1,y1, x2,y2, x3,y3, x4,y4) ((t_xy) { \
    vxs(vxs(x1,y1, x2,y2), (x1)-(x2), vxs(x3,y3, x4,y4), (x3)-(x4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)), \
    vxs(vxs(x1,y1, x2,y2), (y1)-(y2), vxs(x3,y3, x4,y4), (y3)-(y4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)) })

typedef struct	s_scaler
{
	int 		result;
	int			bop;
	int			fd; 
	int			ca;
	int			cache; 
}				t_scaler;

typedef struct		s_line
{
	int				y0;
	int				y1;
	int				x0;
	int				x1;
	int				dx;
	int				dy;
	int				color;
}					t_line;

typedef	struct		s_img
{
	int				*data;
	int				w;
	int				h;
}					t_img;

typedef	struct 		s_f
{
	float			ceil;
	float			floor;
}					t_f;

typedef	struct 		s_ab_i
{
	int				a;
	int				b;
}					t_ab_i;

typedef	struct 		s_ab
{
	float			a;
	float			b;
}					t_ab;

typedef struct		s_xy
{
	float			x;
	float			y;
}					t_xy;

typedef struct		s_xy_i
{
	int				x;
	int				y;
}					t_xy_i;

typedef	struct 		s_xyz
{
	float			x;
	float			y;
	float			z;
}					t_xyz;

typedef struct		s_player
{
	float			angle;
	float			anglesin;
	float			anglecos;
	float			yaw;
	t_xyz			where;
	t_xyz			velocity;
	int				sector;
	int				move;
	int				fall;
	int				ground;
}					t_player;

typedef struct		s_sdl
{
	SDL_Window		*win;
	int				*pix;
	t_line			line;
}					t_sdl;

typedef struct		s_sector
{
	float			ceil;
	float			floor;
	t_xy			*vert;
	int				npoints;
	int				*neighbors;
	int				txtf;
	int				txtc;
	int				txtw;
	t_img			imgfloor;
	t_img			imgceil;
}					t_sector;

typedef struct		s_obj
{
	t_xy			p;
	int				sector;
	int				**images;
	int				anim_count;
	int				anim_frame;
	int				states_count;
	int				states_frame;
	void			(*state_change)(struct s_obj *obj, int state);
	void			(*anim_next)(struct s_obj *obj);
	t_img			(*get_img)(struct s_doom *doom, struct s_obj *obj);
}					t_obj;

/*
typedef struct		s_obj
{
	t_img			img;
	int				anim;
	int				cnt_frms;
	int				rotate;
	float			pov;
	int				txt_ind;
	int				sector;
	t_xy			p;
}					t_obj;
*/

typedef struct		s_cood
{
	int				neighbor;
	int				beginx;
	int				endx;
	float			u0;
	float				u1;
	t_xyz			v1;
	t_xyz			v2;
	t_xyz			t1;
	t_xyz			t2;

	t_xy			org1;
	t_xy			org2;
	int				txtx;
	t_xy			scale1;
	t_xy			scale2;

	t_xy_i			w1;
	t_xy_i			w2;
	t_ab_i			wy;
	t_ab_i			wx;
	t_ab_i			w1y;
	t_ab_i			w2y;
	t_ab_i			n1y;
	t_ab_i			n2y;
	t_f				y;
	t_sector		*s;
}					t_cood;

typedef struct		s_pic
{
	t_img			img;
	int				cnt_frms;
	int				anim;
	int				sector;
	int				wall;
	int				txt_ind;
	float			z;
	t_cood			cood;
	t_xy			p;
	t_xy			p1;
	t_xy			p2;
}					t_pic;

typedef struct 		s_item
{
	int				sx;
	int				ex;
	int				sector;
	int				*ytop;
	int				*ybot;
}					t_item;

typedef struct		s_texture
{
	int				*data;
	int				w;
	int				h;
	int				sector;
	int				ind;
	int				wall;
	int				txt_ind;
}					t_texture;

typedef struct 		s_be
{
	int				begin;
	int				end;
	int				x;
}					t_be;




typedef struct		s_doom
{
	t_sdl			*sdl;
	t_sector		*sector;
	t_obj			*obj;
	t_pic			*pic;
	t_texture		*txt;
	t_player		player;
	t_item			*item;
	t_item			now;
	t_item 			queue[32];
	t_item			*head;
	t_item			*tail;
	t_cood			cood;
	int				a;
	int				olda;
	int				*data;
	int     		numvertexes;
    int     		numsectors;
	int				numobjs;
	int				numpics;
	int				numtxts;
	int				push;
	int				wsad[4];
	int				ybot[WIDTH];
	int				ytop[WIDTH];
	float			*len;
	float			time_old;
	float			time_new;
	float			time_frame;
	struct s_enemy	*enemy;
	t_img			images[512];
	int				images_count;
}					t_doom;

typedef struct		s_enemy
{
	t_obj			*obj;
	//direction vector
	t_xy			dir;
	//rotation is stored in radians
	float			rot;
	//0 - wandering, 1 - attacking
	float			view_distance;
	float			move_speed;
	int				state;
	int				health;
	int				txt_index;
	float			attack_speed;
	float			attack_cd;
	int				attack_damage;
	void			(*on_attack)(t_doom *doom, struct s_enemy *enemy);
	void			(*on_hit)(t_doom *doom, struct s_enemy *enemy);
	void			(*on_framestart)(t_doom *doom, struct s_enemy *enemy);
}					t_enemy;

int		initall(t_doom *doom);
int		loadall(t_doom *doom);
int		countall(t_doom *doom, char **map);
int		loadvertexes(t_xy *v, char *str);
int		loadsectors(t_sector *s, t_xy *v, char *str);
int		loadobjs(t_obj *obj, char *str);
int		loadpics(t_pic *pic, char *str);
int		loadtxts(t_texture *txt, char *str);
int		loadplayer(t_player *player, char *str);

int		loadtextures(t_doom *doom);

float	vxs(float x0, float y0, float x1, float y1);
char	*todigit(char *str, float *data);
int		hooks(t_doom *doom, SDL_Event ev);
int		loadgame(t_doom *doom);
int		drawscreen(t_doom *doom);
int		drawsprites(t_doom *doom, t_obj *obj, t_player player);
float	yaw(float y, float z, t_player player);
t_enemy	*create_enemy(t_doom *doom, t_obj *obj);
void	enemies_update(t_doom *doom);


#endif
