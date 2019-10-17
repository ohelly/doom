/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sel_sprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:07:08 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/17 16:10:15 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void	sel_sprite(int x, int y, t_all_spr_floor *obj, t_all_spr_wall *aspr)
{
	if (x >= 950 && x <= 1000 && y >= 110 && y <= 160)
	{
		if (aspr->select_spr == -1 || obj->select_obj != -1)
		{
			sv(&aspr->select_spr, &obj->select_obj);
			return ;
		}
		aspr->select_spr == 0 ? aspr->select_spr = aspr->count - 1 :
		aspr->select_spr--;
	}
	else if (x >= 1200 && x <= 1250 && y >= 110 && y <= 160)
	{
		if (aspr->select_spr == -1 || obj->select_obj != -1)
		{
			sv(&aspr->select_spr, &obj->select_obj);
			return ;
		}
		aspr->select_spr == aspr->count - 1 ? aspr->select_spr = 0 :
		aspr->select_spr++;
	}
}