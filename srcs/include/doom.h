/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 18:17:38 by dtoy              #+#    #+#             */
/*   Updated: 2019/09/01 19:17:45 by dtoy             ###   ########.fr       */
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
# include <SDL2/SDL.h>
# define BUFF_SIZE 1

# define WIDTH 1280
# define HEIGHT 720
# define hfov (0.73f * HEIGHT)
# define vfov (.2f * HEIGHT)
 
# define min(a,b)             (((a) < (b)) ? (a) : (b))
# define max(a,b)             (((a) > (b)) ? (a) : (b))
# define clamp(a, mi,ma)      min(max(a,mi),ma)        
# define vxs(x0,y0, x1,y1)    ((x0)*(y1) - (x1)*(y0))   // vxs: Vector cross product
# define Intersect(x1,y1, x2,y2, x3,y3, x4,y4) ((struct xy1) { \
    vxs(vxs(x1,y1, x2,y2), (x1)-(x2), vxs(x3,y3, x4,y4), (x3)-(x4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)), \
    vxs(vxs(x1,y1, x2,y2), (y1)-(y2), vxs(x3,y3, x4,y4), (y3)-(y4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)) })


typedef struct	s_xy
{
	float x;
	float y; 
}				t_xy;

typedef struct	s_sector
{
    float		floor;
	float		ceil;
	t_xy		*vertex;
    int         *neighbors;
    int			npoints;
}				t_sector;

typedef	struct		s_player
{
    struct	xyz
	{
		float		x;
		float		y;
		float		z;
	}	where,
		velocity;
    float			angle;
	float			anglesin;
	float			anglecos;
    int				sector;
}					t_player;

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

typedef struct  	s_doom
{
    t_sdl			*sdl;
    t_sector		*sectors;
    t_player		*player;
	int     		numvertexes;
    int     		numsectors;
    char    		**map;
}               	t_doom;

int					get_next_line(const int fd, char **line);
int					loadmap(t_doom *doom);
int					loadsectors(t_doom *doom, t_xy *vert, char *str);
int					sdlstart(t_doom *doom);
int					hooks(t_doom *doom, SDL_Event ev);
int					drawgame(t_doom *doom, t_player *player);
int					line(t_sdl *sdl);
#endif
