/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:07:27 by glormell          #+#    #+#             */
/*   Updated: 2019/10/30 21:17:18 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H
# include "doom.h"
# include "utils.h"

# define MENU_WIDTH				300
# define MENU_HEIGHT			240
# define BTN_HEIGHT				40

typedef struct				s_doom	t_doom;

typedef struct				s_menu_button
{
	t_ab_i					p;
	t_ab_i					s;
	t_hudel					he;
	int						h;
	int						a;
	int						d;
	int						color;
	int						s_color;
	int						h_color;
	int						a_color;
	int						d_color;
	void					(*click)(struct s_doom *doom,
										struct s_menu_button *b);
	struct s_menu_button	*next;
}							t_menu_button;

typedef struct				s_menu
{
	TTF_Font				*font;
	int						s;
	int						h;
	t_ab_i					p;
	int						i;
	int						c;
	int						l;
	t_menu_button			*btns;
	t_menu_button			*s_btn;
}							t_menu;

#endif
