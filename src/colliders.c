/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colliders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:19:06 by njacobso          #+#    #+#             */
/*   Updated: 2019/10/29 17:28:55 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** returns 1 if two circle colliders with given radiuses overlap
*/

int		collision_circle(t_xy pos1, float rad1, t_xy pos2, float rad2)
{
	if (distance(pos1, pos2) < (rad1 + rad2))
		return (1);
	return (0);
}

/*
** returns 1 if box colliders overlap
*/

int		collision_box(t_xy p1, t_xy p2, t_xy v1, t_xy v2)
{
	return (Overlap(p1.x, p2.x, v1.x, v2.x) && Overlap(p1.y, p2.y, v1.y, v2.y));
}

/*
** returns 1 if box colliders overlap AND pointside <= 0
*/

int		collision_box_dir(t_xy pos1, t_xy pos2, t_xy col_pos1, t_xy col_pos2)
{
	if (IntersectBox(pos1.x, pos1.y, pos2.x, pos2.y, col_pos1.x, col_pos1.y,
												col_pos2.x, col_pos2.y) &&
		PointSide(pos2.x, pos2.y, col_pos1.x, col_pos1.y,
											col_pos2.x, col_pos2.y) <= 0)
		return (1);
	return (0);
}
