/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sel_texture_wall.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 14:56:25 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/17 15:00:24 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void		sel_texture_wall(int x, int y, t_all_walls *walls)
{
	if (x >= 950 && x <= 1000 && y >= 660 && y <= 710)
		walls->wall[walls->selected_wall].txt == 0 ?
		walls->wall[walls->selected_wall].txt = COUNT_T - 1 :
		walls->wall[walls->selected_wall].txt--;
	else
		walls->wall[walls->selected_wall].txt == COUNT_T - 1 ?
		walls->wall[walls->selected_wall].txt = 0 :
		walls->wall[walls->selected_wall].txt++;
}
