/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_click.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 19:22:32 by glormell          #+#    #+#             */
/*   Updated: 2019/10/29 20:17:09 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			menu_click(t_doom *doom, t_menu_button *b)
{
	doom->menu.btn.a = !(b == &doom->menu.btn && !doom->menu.btn.d);
	if (b == &doom->menu.btn && !doom->menu.btn.d)
		return ;
}
