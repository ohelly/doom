/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.h                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 19:45:10 by dtoy              #+#    #+#             */
/*   Updated: 2019/09/26 20:33:23 by dtoy             ###   ########.fr       */
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
# define EyeHeight  10
# define DuckHeight 2.5
# define HeadMargin 1
# define KneeHeight 2
# define HFOV (1.0 * 0.73f * HEIGHT / WIDTH)
# define VFOV (1.0 * .2f)
# define MIN(a,b)             (((a) < (b)) ? (a) : (b))
# define MAX(a,b)             (((a) > (b)) ? (a) : (b))
# define CLAMP(a, mi,ma)      min(max(a,mi),ma)
# define VXS(x0,y0, x1,y1)    ((x0)*(y1) - (x1)*(y0))
# define Overlap(a0,a1,b0,b1) (min(a0,a1) <= max(b0,b1) && min(b0,b1) <= max(a0,a1))
# define IntersectBox(x0,y0, x1,y1, x2,y2, x3,y3) (Overlap(x0,x1,x2,x3) && Overlap(y0,y1,y2,y3))
# define PointSide(px,py, x0,y0, x1,y1) vxs((x1)-(x0), (y1)-(y0), (px)-(x0), (py)-(y0))
# define Intersect(x1,y1, x2,y2, x3,y3, x4,y4) ((struct xy1) { \
    vxs(vxs(x1,y1, x2,y2), (x1)-(x2), vxs(x3,y3, x4,y4), (x3)-(x4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)), \
    vxs(vxs(x1,y1, x2,y2), (y1)-(y2), vxs(x3,y3, x4,y4), (y3)-(y4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)) })

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

typedef	struct 		s_ab
{
	float			a;
	float			b;
}					t_ab;

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
	int				jump;
	int				ground;
}					t_player;

typedef struct		s_sdl
{
	SDL_Window		*win;
	int				*pix;
	t_line			line;
}					t_sdl;

typedef struct		s_xy
{
	float			x;
	float			y;
}					t_xy;

typedef struct		s_sector
{
	float			ceil;
	float			floor;
	t_xy			*vert;
	int				npoints;
	int				*neighbors;
}					t_sector;

typedef struct		s_obj
{
	int				**data;
	int				cnt_frms;
	int				anim;
	int				rotate;
	float			pov;
	int				w;
	int				h;
	int				txt_ind;
	t_xy			v;
}					t_obj;

typedef struct		s_pic
{
	int				**data;
	int				cnt_frms;
	int				anim;
	int				w;
	int				h;
	int				z;
	t_xy			v1;
	t_xy			v2;
}					t_pic;

typedef struct 		s_item
{
	int				sx;
	int				ex;
	int				sector;
}					t_item;

typedef struct		s_texture
{
	int				*data;
	int				w;
	int				h;
}					t_texture;

typedef struct		s_doom
{
	t_sdl			sdl;
	t_sector		*sector;
	t_obj			*obj;
	t_pic			*pic;
	t_texture		*txt;
	t_player		player;
	t_item			item;
	int     		numvertexes;
    int     		numsectors;
	int				numobjs;
	int				numpics;
	int				numtxt;
}					t_doom;

#endif
