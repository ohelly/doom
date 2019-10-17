/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_press_left_thr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:59:48 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/15 15:00:21 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void		mouse_press_left_thr(t_doom *doom, int x, int y)
{
	if (x >= 950 && x <= 1000 && y >= 10 && y <= 60)
	{
		if (doom->obj->select_obj == -1 || doom->aspr->select_spr != -1)
		{
			doom->obj->select_obj = 0;
			doom->aspr->select_spr = -1;
			return ;
		}
		if (doom->obj->count < 2)
			return ;
		if (doom->obj->select_obj == 0)
			doom->obj->select_obj = doom->obj->count;
		doom->obj->select_obj--;
	}
	else if (x >= 1200 && x <= 1250 && y >= 10 && y <= 60)
	{
		if (doom->obj->select_obj == -1 || doom->aspr->select_spr != -1)
		{
			doom->obj->select_obj = 0;
			doom->aspr->select_spr = -1;
			return ;
		}
		if (doom->obj->count < 2)
			return ;
		if (doom->obj->select_obj == doom->obj->count - 1)
			doom->obj->select_obj = -1;
		doom->obj->select_obj++;
	}
	else if (x >= 950 && x <= 1000 && y >= 110 && y <= 160)
	{
		if (doom->aspr->select_spr == -1 || doom->obj->select_obj != -1)
		{
			doom->aspr->select_spr = 0;
			doom->obj->select_obj = -1;
			return ;
		}
		if (doom->aspr->count < 2)
			return ;
		if (doom->aspr->select_spr == 0)
			doom->aspr->select_spr = doom->aspr->count;
		doom->aspr->select_spr--;
	}
	else if (x >= 1200 && x <= 1250 && y >= 110 && y <= 160)
	{
		if (doom->aspr->select_spr == -1 || doom->obj->select_obj != -1)
		{
			doom->aspr->select_spr = 0;
			doom->obj->select_obj = -1;
			return ;
		}
		if (doom->aspr->count < 2)
			return ;
		if (doom->aspr->select_spr == doom->aspr->count - 1)
			doom->aspr->select_spr = -1;
		doom->aspr->select_spr++;
	}
}