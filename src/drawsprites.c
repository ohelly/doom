/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawsprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 11:56:24 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/28 17:38:03 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			findobjslen(t_doom *doom, t_obj *obj, float *len, t_player player)
{
	int		n;

	n = 0;
	while (n < doom->num.objs)
	{
		len[n] = sqrtf(powf(obj[n].p.x - player.where.x, 2) +
		powf(obj[n].p.y - player.where.y, 2));
		n++;
	}
	return (0);
}

void		swap(int *order, float *len, int n)
{
	int		tmp;
	float	l;

	tmp = order[n + 1];
	order[n + 1] = order[n];
	order[n] = tmp;
	l = len[n + 1];
	len[n + 1] = len[n];
	len[n] = l;
}

void		renew_order(int *order, t_doom *doom)
{
	int		j;

	j = 0;
	while (j < doom->num.objs)
	{
		doom->obj_ind[j] = 0;
		order[j] = j;
		j++;
	}
}

int			*sortobjs(t_doom *doom, int *order, t_player player)
{
	int		n;
	int		j;
	float	l;
	float	len[doom->num.objs];
	int		tmp;

	findobjslen(doom, doom->objs, len, player);
	ft_memmove(doom->len, len, doom->num.objs * 4);
	renew_order(order, doom);
	j = 0;
	n = 0;
	while (j < doom->num.objs)
	{
		n = 0;
		while (n < doom->num.objs - 1)
		{
			if (len[n] < len[n + 1])
				swap(order, len, n);
			n++;
		}
		j++;
	}
	return (order);
}

int			drawsprites(t_doom *doom, t_obj *obj, t_player player)
{
	int		n;
	t_obj	*o;
	int		j;

	sortobjs(doom, doom->order, doom->player);
	n = 0;
	while (n < doom->num.objs)
	{
		o = &doom->objs[doom->order[n]];
		doom->obj_num = o->n;
		if (!doom->item[o->sector].sector || doom->len[n] < 3.f)
		{
			n++;
			continue ;
		}
		if (!(drawobj(doom, o, o->p)))
		{
			n++;
			continue ;
		}
		n++;
	}
	return (0);
}
