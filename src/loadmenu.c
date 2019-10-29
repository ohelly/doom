/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadmenu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 15:33:43 by glormell          #+#    #+#             */
/*   Updated: 2019/10/29 20:24:38 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			load_menu(t_doom *doom)
{
	SDL_SetRelativeMouseMode(0);
	doom->menu.s = 0;
	doom->menu.p = (t_ab_i){ 20, 20 };
	load_menu_button1(doom, doom->menu);
}
