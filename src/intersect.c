/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:16:38 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/28 17:17:25 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_xy		findintersect(t_xyz *t1, t_xyz *t2, int sign)
{
	t_xy	i;

	i.x = vxs(vxs(t1->x, t1->z, t2->x, t2->z), t1->x - t2->x,
	vxs(NEARSIDE * sign, NEARZ, FARSIDE * sign, FARZ),
	NEARSIDE * sign - FARSIDE * sign)
	/ vxs(t1->x - t2->x, t1->z - t2->z, NEARSIDE *
	sign - FARSIDE * sign, NEARZ - FARZ);
	i.y = vxs(vxs(t1->x, t1->z, t2->x, t2->z), t1->z - t2->z,
	vxs(NEARSIDE * sign, NEARZ, FARSIDE * sign, FARZ),
	NEARZ - FARZ)
	/ vxs(t1->x - t2->x, t1->z - t2->z, NEARSIDE *
	sign - FARSIDE * sign, NEARZ - FARZ);
	return (i);
}

void		iflower(t_xyz *t, t_xy i1, t_xy i2)
{
	if (i1.y > 0)
	{
		t->x = i1.x;
		t->z = i1.y;
	}
	else
	{
		t->x = i2.x;
		t->z = i2.y;
	}
}

int			txt_resolution(t_cood *cood)
{
	if (fabs(cood->t2.x - cood->t1.x) > fabs(cood->t2.z - cood->t1.z))
	{
		cood->u0 = (cood->t1.x - cood->org1.x) *
		cood->u1 / (cood->org2.x - cood->org1.x);
		cood->u1 = (cood->t2.x - cood->org1.x) *
		cood->u1 / (cood->org2.x - cood->org1.x);
	}
	else
	{
		cood->u0 = (cood->t1.z - cood->org1.y) *
		cood->u1 / (cood->org2.y - cood->org1.y);
		cood->u1 = (cood->t2.z - cood->org1.y) *
		cood->u1 / (cood->org2.y - cood->org1.y);
	}
	return (0);
}

int			intersect(t_xyz *t1, t_xyz *t2, t_cood *cood)
{
	t_xy	i1;
	t_xy	i2;

	i1 = findintersect(t1, t2, -1);
	i2 = findintersect(t1, t2, 1);
	cood->org1.x = t1->x;
	cood->org1.y = t1->z;
	cood->org2.x = t2->x;
	cood->org2.y = t2->z;
	if (t1->z < NEARZ)
		iflower(t1, i1, i2);
	if (t2->z < NEARZ)
		iflower(t2, i1, i2);
	txt_resolution(cood);
	return (0);
}
