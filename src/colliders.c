/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colliders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:19:06 by njacobso          #+#    #+#             */
/*   Updated: 2019/10/29 01:53:34 by dtoy             ###   ########.fr       */
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
	return (overlap(p1.x, p2.x, v1.x, v2.x) && overlap(p1.y, p2.y, v1.y, v2.y));
}

/*
** returns 1 if box colliders overlap AND pointside <= 0
*/

int		collision_box_dir(t_xy pos1, t_xy pos2, t_xy col_pos1, t_xy col_pos2)
{
	if ((intersect_box(pos1, pos2, col_pos1, col_pos2) &&
		point_side(pos2, col_pos1, col_pos2) <= 0))
		return (1);
	return (0);
}
