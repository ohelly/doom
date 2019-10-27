/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sel_txt_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 13:58:03 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/27 14:05:02 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void		sel_txt_obj(int x, int y, t_all_spr_floor *obj)
{
	if (x >= 950 && x <= 1000 && y >= 60 && y <= 110)
	{
		obj->obj[obj->select_obj].txt == 0 ?
		obj->obj[obj->select_obj].txt = COUNT_OP - 1 :
		obj->obj[obj->select_obj].txt--;
	}
	else
	{
		obj->obj[obj->select_obj].txt == COUNT_OP - 1 ?
		obj->obj[obj->select_obj].txt = 0 :
		obj->obj[obj->select_obj].txt++;
	}
}
