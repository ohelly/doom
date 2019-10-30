/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadmenuclick.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 22:11:29 by glormell          #+#    #+#             */
/*   Updated: 2019/10/30 20:18:37 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void				menu_button1_click(struct s_doom *doom,
										struct s_menu_button *b)
{
	(void)doom;
	(void)b;
	printf("Click 1\n");
}

void				menu_button2_click(struct s_doom *doom,
										struct s_menu_button *b)
{
	(void)doom;
	(void)b;
	printf("ti pidor\n");
}

void				menu_button3_click(struct s_doom *doom,
										struct s_menu_button *b)
{
	(void)doom;
	(void)b;
}

void				menu_button4_click(struct s_doom *doom,
										struct s_menu_button *b)
{
	(void)doom;
	(void)b;
	exit(0);
}
