/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadmenuclick.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 22:11:29 by glormell          #+#    #+#             */
/*   Updated: 2019/10/30 21:38:32 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void				menu_button1_click(struct s_doom *doom,
										struct s_menu_button *b)
{
	(void)b;
	doom->menu.s = 0;
	doom->difficult = 1;
}

void				menu_button2_click(struct s_doom *doom,
										struct s_menu_button *b)
{
	(void)b;
	doom->menu.s = 0;
	doom->difficult = 2;
}

void				menu_button3_click(struct s_doom *doom,
										struct s_menu_button *b)
{
	(void)b;
	doom->menu.s = 0;
	doom->difficult = 3;
}

void				menu_button4_click(struct s_doom *doom,
										struct s_menu_button *b)
{
	(void)b;
	quit(doom);
}
