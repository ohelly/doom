/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:20:36 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/27 20:20:51 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_scaler	scaler_init(t_ab_i wy, int cya, int u0, int u1)
{
	t_scaler t;

	if ((wy.b - wy.a) == 0)
		wy.b -= 1;
	t.result = (u0 + (cya - 1 - wy.a) * (u1 - u0) / (wy.b - wy.a));
	t.bop = ((u1 < u0) ^ ((wy.b < wy.a)) ? -1 : 1);
	t.fd = abs(u1 - u0);
	t.ca = abs(wy.b - wy.a);
	t.cache = (cya - 1 - wy.a) * abs(u1 - u0) % abs(wy.b - wy.a);
	return (t);
}

int		scaler_next(t_scaler* i)
{
    for (i->cache += i->fd; i->cache >= i->ca; i->cache -= i->ca)
		i->result += i->bop;
    return (i->result);
}
