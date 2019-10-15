/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 19:45:10 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/15 19:33:06 by dtoy             ###   ########.fr       */
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

# define WIDTH 1280
# define HEIGHT 720
# define NEARZ 1e-4f
# define FARZ 5
# define NEARSIDE 1e-5f
# define FARSIDE 20.f
# define EyeHeight  15
# define DuckHeight 2.5
# define HeadMargin 1
# define KneeHeight 2
# define HFOV (0.73f * HEIGHT / WIDTH)
# define VFOV (0.2f)
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

typedef struct	s_xy
{
	float		x;
	float		y;
}				t_xy;

typedef	struct 	s_xyz
{
	float		x;
	float		y;
	float		z;
}				t_xyz;

typedef	struct 	s_ab_i
{
	int			a;
	int			b;
}				t_ab_i;

typedef struct	s_img
{
	int			*data;
	int			w;
	int			h;
}				t_img;

typedef struct	s_texture
{
	int			image;
}				t_texture;

typedef struct	s_obj
{
	t_xy		p;
	int			sector;
	int			type;
	int			**images;
	int			*anim_count;
	int			anim_frame;
	int			states_count;
	int			states_frame;
}				t_obj;

typedef struct	s_data
{
	int			type;
	int			**images;
	int			*anim_count;
	int			states_count;
}				t_data;

typedef struct	s_pics
{
	t_xyz		p;
	t_xy		p1;
	t_xy		p2;
	int			sector;
	int			type;
	int			wall;
	int			**images;
	int			*anim_count;
	int			anim_frame;
	int			states_count;
	int			states_frame;
}				t_pics;

typedef struct		s_player
{
	float		angle;
	float		psin;
	float		pcos;
	float		yaw; //look up/down
	t_xyz		where;
	t_xyz		velocity;
	int			sector;
	int			move; // player moving
	int			sit; // crouch
	int			stand; 
	int			fall; // jump or fall
	int			ground; // player on the ground (fall = !ground)
	int			start;
	int			end;
	int			weapon;
	int			hp;
}				t_player;

typedef	struct	s_cood
{
	int			x;
	int			y;
	int			n;
	int			neighbor;
	int			beginx;
	int			endx;
	float		u0;
	float		u1;
	int			yceil;
	int			yfloor;
	int			nyceil;
	int			nyfloor;
	int			txtx;
	int			ptxtx;
	int			piccount;
	int			picnum[32];
	int			num;
	float		pu0[32];
	float		pu1[32];
	int			pyceil[32];
	int			pyfloor[32];
	t_xyz		pv1[32];
	t_xyz		pv2[32];
	t_xyz		pt1[32];
	t_xyz		pt2[32];
	t_xy		porg1[32]; 
	t_xy		porg2[32];
	t_xy		pscale1[32];
	t_xy		pscale2[32];
	int			pw1x[32];
	int			pw2x[32];
	t_ab_i		pwy[32]; 
	t_ab_i		pwx[32]; //current point
	t_ab_i		pcy[32];
	t_ab_i		pw1y[32];
	t_ab_i		pw2y[32];

	t_xyz		v1;
	t_xyz		v2;
	t_xyz		t1;
	t_xyz		t2;
	t_xy		org1; 
	t_xy		org2;
	t_xy		scale1;
	t_xy		scale2;
	int			w1x; //left point
	int			w2x; //right point
	t_ab_i		wy; 
	t_ab_i		wx; //current point
	t_ab_i		cy;
	t_ab_i		w1y;
	t_ab_i		w2y;
	t_ab_i		ny;
	t_ab_i		nx;
	t_ab_i		cny;
	t_ab_i		n1y;
	t_ab_i		n2y;
}				t_cood;

typedef struct	s_sectors
{
	t_xy		*vert; //vertices
	float		constceil; //constceil for door/elevator
	//float		constfloor; //constfloor for elevator
	float		ceil;
	float		floor;
	float		light;
	int			type; //door or elevator
	int			active; //door or elevetor going up/down (open/close)
	int			open; //for elevator top position
	int			close; //bottom
	int			npoints; //vertices count
	int			*neighbors; //neighbour sectors
	int			txtf; //floor
	int			txtc; //ceil
	int			*txtw; //wall
	int			sky;
}				t_sectors;

typedef struct	s_line
{
	int			y0;
	int			y1;
	int			x0;
	int			x1;
	int			dx;
	int			dy;
	int			color;
}				t_line;

typedef struct	s_sdl
{
	SDL_Window	*win;
	int			*pix;
	t_line		line;
}				t_sdl;

typedef struct	s_num
{
	int     	vertexes;
	int			weapons;
    int     	sectors;
	int			objs;
	int			pics;
	int			txts;
}				t_num;

typedef struct	s_weapon
{
	int			type;
	int			**images;
	int			*anim_count;
	int			anim_frame;
	int			states_count;
	int			states_frame;
}				t_weapon;

typedef struct	s_fps
{
	float		times[32];
	float		time_frame;
}				t_fps;

typedef struct 	s_item
{
	int			sx;
	int			ex;
	int			sector;
	int			*ytop;
	int			*ybot;
}				t_item;

typedef struct	s_doom
{
	t_img		img[512];
	t_weapon	*weapon;
	t_texture	*sky;
	t_texture	*walls;
	t_texture	*floors;
	t_texture	*ceils;
	t_obj		*objs;
	t_data		*objs_data;
	t_pics		*pics;
	t_data		*pics_data;
	t_sectors	*sectors;
	t_sdl		*sdl;
	t_player	player;
	t_num		num;
	t_fps		fps;
	t_item 		queue[32];
	t_item		*head;
	t_item		*tail;
	t_item		*item;
	t_item		now;
	t_cood		cood;
	int			wsad[4];
	int			visible[HEIGHT][WIDTH];
	int			ytop[WIDTH];
	int			ybot[WIDTH];
	int			push;
	int			a;
	int			lkey;
	int			rkey;
}				t_doom;


int		loadall(t_doom *doom);
int		initall(t_doom *doom);
int		countall(t_doom *doom, char **map);
int		loadvertexes(t_xy *v, char *str);
int		loadsectors(t_sectors *s, t_xy *v, char *str);
char	*todigit(char *str, float *data);
int		loadobjs(t_obj *obj, t_data *objs_data, char *str);
int		loadpics(t_doom *doom, t_pics *pic, t_data *pics_data, char *str);
int		loadplayer(t_player *player, char *str);
int		load_game(t_doom *doom);
int		hooks(t_doom *doom, SDL_Event ev);
int		profile_output(t_doom *doom);
int		draw_screen(t_doom *doom);
int		draw_walls(t_doom *doom, t_player player);
int		rgb_multiply(int color, float value);
float	vxs(float x0, float y0, float x1, float y1);
float	yaw(float y, float z, t_player player);
void	drawweapon(t_doom *doom, t_weapon *weapon);
t_img	weapon_get_image(t_doom *doom, t_weapon *weapon);

#endif
