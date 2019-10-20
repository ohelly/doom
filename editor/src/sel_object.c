/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sel_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 15:55:23 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/17 16:01:17 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void	sel_object(int x, int y, t_all_spr_floor *obj, t_all_spr_wall *aspr)
{
	if (x >= 950 && x <= 1000 && y >= 10 && y <= 60)
	{
		if (obj->select_obj == -1 || aspr->select_spr != -1)
		{
			sv(&obj->select_obj, &aspr->select_spr);
			return ;
		}
		obj->select_obj == 0 ? obj->select_obj = obj->count - 1 :
		obj->select_obj--;
	}
	else
	{
		if (obj->select_obj == -1 || aspr->select_spr != -1)
		{
			sv(&obj->select_obj, &aspr->select_spr);
			return ;
		}
		obj->select_obj == obj->count - 1 ? obj->select_obj = 0 :
		obj->select_obj++;
	}
}
