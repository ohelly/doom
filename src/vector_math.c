/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:22:50 by njacobso          #+#    #+#             */
/*   Updated: 2019/10/23 17:23:10 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_xy	rot_to_v2(float rot)
{
	t_xy	v2;

	v2.x = cos(rot);
	v2.y = sin(rot);
	return (v2);
}

float	v2_to_rot(t_xy v2)
{
	return (atan2(v2.y, v2.x));
}

t_xy	v2_add(t_xy v1, t_xy v2)
{
	t_xy tmp;

	tmp.x = v1.x + v2.x;
	tmp.y = v1.y + v2.y;
	return (tmp);
}

t_xy	v2_addf(t_xy v2, float f)
{
	t_xy tmp;

	tmp.x = v2.x + f;
	tmp.y = v2.y + f;
	return (tmp);
}

t_xy	v2_subtract(t_xy v1, t_xy v2)
{
	t_xy tmp;

	tmp.x = v1.x - v2.x;
	tmp.y = v1.y - v2.y;
	return (tmp);
}

t_xy	v2_multf(t_xy v2, float f)
{
	t_xy tmp;

	tmp.x = v2.x * f;
	tmp.y = v2.y * f;
	return (tmp);
}

float	distance(t_xy p1, t_xy p2)
{
	t_xy	tmp;
	float	distance;

	tmp.x = p2.x - p1.x;
	tmp.y = p2.y - p1.y;
	distance = sqrt((tmp.x * tmp.x) + (tmp.y * tmp.y));
	return (distance);
}

float	rad_to_deg(float rad)
{
	return (rad * (180 / M_PI));
}

t_xy	v2_normalize(t_xy v2)
{
	t_xy	tmp;
	float	w;

	tmp = v2;
	w = sqrt(tmp.x * tmp.x + tmp.y * tmp.y);
	tmp.x /= w;
	tmp.y /= w;
	return (tmp);
}
