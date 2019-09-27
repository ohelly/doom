/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 18:17:38 by dtoy              #+#    #+#             */
/*   Updated: 2019/09/26 20:22:15 by dtoy             ###   ########.fr       */
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
# define PLUS +
# define MINUS -
# define EyeHeight  10
# define DuckHeight 2.5
# define HeadMargin 1
# define KneeHeight 2
# define hfov (1.0 * 0.73f * HEIGHT / WIDTH)
# define vfov (1.0 * .2f)
# define min(a,b)             (((a) < (b)) ? (a) : (b))
# define max(a,b)             (((a) > (b)) ? (a) : (b))
# define clamp(a, mi,ma)      min(max(a,mi),ma)        
# define vxs(x0,y0, x1,y1)    ((x0)*(y1) - (x1)*(y0))  
# define Overlap(a0,a1,b0,b1) (min(a0,a1) <= max(b0,b1) && min(b0,b1) <= max(a0,a1))
# define IntersectBox(x0,y0, x1,y1, x2,y2, x3,y3) (Overlap(x0,x1,x2,x3) && Overlap(y0,y1,y2,y3))
# define PointSide(px,py, x0,y0, x1,y1) vxs((x1)-(x0), (y1)-(y0), (px)-(x0), (py)-(y0))
# define Intersect(x1,y1, x2,y2, x3,y3, x4,y4) ((struct xy1) { \
    vxs(vxs(x1,y1, x2,y2), (x1)-(x2), vxs(x3,y3, x4,y4), (x3)-(x4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)), \
    vxs(vxs(x1,y1, x2,y2), (y1)-(y2), vxs(x3,y3, x4,y4), (y3)-(y4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)) })


typedef struct	s_xyzwh
{
	float	x;
	float	y;
	float	top;
	float	bot;
	int		text_ind;
	int		sector;
	int		visible;

}				t_xyzwh;

typedef struct		s_xy
{
	float			x;
	float			y;
}					t_xy;

typedef struct		s_xyab
{
	float			xa;
	float			ya;
	float			xb;
	float			yb;
}					t_xyab;


typedef	struct		s_player
{
    struct	xyz
	{
		float		x;
		float		y;
		float		z;
	}				where, velocity;
    float			angle;
	float			anglesin;
	float			anglecos;
    int				sector;
	float			yaw;
	int				move;
	int				fall;
	int				ground;
}					t_player;


typedef struct	s_sector
{
    float		floor;
	float		ceil;
	t_xy		*vertex;
    int         *neighbors;
    int			npoints;
	int			ybot[WIDTH];
	int			ytop[WIDTH];
	int			sx;
	int			ex;
}				t_sector;

typedef struct		s_line
{
	int		y0;
	int		y1;
	int		x0;
	int		x1;
	int		dx;
	int		dy;
	int		color;
}					t_line;

typedef struct		s_sdl
{
	SDL_Window		*win;
	SDL_Surface		*surface;
	int				*pix;
	t_line			*line;
}					t_sdl;

typedef struct		s_stock
{
	int		sector;
	int		sx;
	int		ex;
}					t_stock;

typedef struct		s_item
{
	int				sx;
	int				ex;
	int				sector;
	int				ytop[WIDTH];
	int				ybot[WIDTH];
}					t_item;

typedef struct s_data
{
	int			*data[6];
	int			w[6];
	int			h[6];
}				t_data;

typedef struct s_walls
{
	int			*data;
	int			w;
	int			h;
}				t_walls;

typedef struct s_textures
{
	t_data		*spr_data;
	t_walls		*walls;
}				t_textures;


typedef struct  	s_doom
{
    t_sdl			*sdl;
    t_sector		*sectors;
    t_player		*player;
	t_xyzwh			*spr_stock;
	t_item			*item;
	t_textures		*textures;
	int				*svidetel;
	int				*rensects;
	int     		numvertices;
    int     		numsectors;
	int				numsprites;
    char    		**map;
	int				push;
	int				wsad[4];
	int				neighbor;
	int				ytop[WIDTH];
	int				ybot[WIDTH];
	t_stock			*stock;
	float				yceil;
	float				yfloor;
	float				nyceil;
	float				nyfloor;
	int					beginx;
	int					endx;			
	int					a;
	int				jopa;
}               	t_doom;



int		init_all(t_doom *doom);
int		loadmap(t_doom *doom);
int		laodvertices(t_doom *doom, t_xy *v, char *str);
int		loadsectors(t_doom *doom, t_xy *vert, char *str);
int		loadplayer(t_player *player, char *str);
int		loadsprites(t_xyzwh *spr_stock, char *str);
int		drawgame(t_doom *doom, t_player *player);
int		line(t_sdl *sdl);

#endif
