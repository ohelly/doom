/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_menu_button.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:07:27 by glormell          #+#    #+#             */
/*   Updated: 2019/10/30 14:18:26 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H
# include "doom.h"
# include "utils.h"

# define MENU_WIDTH				300
# define MENU_HEIGHT			240
# define BTN_HEIGHT				40

typedef struct				s_menu_button
{
	t_ab_i					p;
	t_ab_i					s;
	t_hudel					he;
	int						h;
	int						a;
	int						d;
	int						color;
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
	t_ab_i					p;
	t_menu_button			*btns;
	t_menu_button			btn1;
	t_menu_button			btn2;
	t_menu_button			btn3;
	t_menu_button			btn4;
	t_menu_button			btn5;
}							t_menu;

#endif
