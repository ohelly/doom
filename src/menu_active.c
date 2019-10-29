/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_active.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 20:04:39 by glormell          #+#    #+#             */
/*   Updated: 2019/10/29 20:04:56 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			menu_active(t_doom *doom, t_menu_button *b)
{
	doom->menu.btn.a = b == &doom->menu.btn && !doom->menu.btn.d;
}
