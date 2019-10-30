/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_hud.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:11:31 by glormell          #+#    #+#             */
/*   Updated: 2019/10/30 14:17:24 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUD_H
# define HUD_H

typedef struct		s_hudel
{
	TTF_Font		*f;
	char			*t;
	SDL_Surface		*s;
	unsigned char	*p;
	int				w;
	int				h;
	int				x;
	int				y;
	int				c;
	int				b;
	int				bc;
}					t_hudel;

typedef struct		s_hud
{
	TTF_Font		*font;
	t_hudel			health;
	t_hudel			ammo;
	struct s_obj	*key;
}					t_hud;

#endif
