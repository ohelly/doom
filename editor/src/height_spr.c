/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   height_spr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 19:05:49 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/20 19:13:31 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void	height_spr(int x, int y, t_all_spr_wall *aspr, t_all_sect *sectors)
{
	if (aspr->select_spr == -1)
		return ;
	if (x >= 950 && x <= 1000 && y >= 210 && y <= 260)
	{
		aspr->spr[aspr->select_spr].z ==
		sectors->sectors[aspr->spr[aspr->select_spr].sector].floor ?
		aspr->spr[aspr->select_spr].z =
		sectors->sectors[aspr->spr[aspr->select_spr].sector].ceiling :
		aspr->spr[aspr->select_spr].z--;
	}
	else
	{
		aspr->spr[aspr->select_spr].z ==
		sectors->sectors[aspr->spr[aspr->select_spr].sector].ceiling ?
		aspr->spr[aspr->select_spr].z =
		sectors->sectors[aspr->spr[aspr->select_spr].sector].floor :
		aspr->spr[aspr->select_spr].z++;
	}
}
