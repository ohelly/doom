/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sel_txt_spr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 19:05:11 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/27 12:38:36 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void	sel_txt_spr(int x, int y, t_all_spr_wall *aspr)
{
	if (x >= 950 && x <= 1000 && y >= 160 && y <= 210)
	{
		aspr->spr[aspr->select_spr].txt == 0 ?
		aspr->spr[aspr->select_spr].txt = COUNT_SP - 1 :
		aspr->spr[aspr->select_spr].txt--;
	}
	else
	{
		aspr->spr[aspr->select_spr].txt == COUNT_SP - 1 ?
		aspr->spr[aspr->select_spr].txt = 0 :
		aspr->spr[aspr->select_spr].txt++;
	}
}
