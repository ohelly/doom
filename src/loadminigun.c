/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadminigun.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 20:11:35 by glormell          #+#    #+#             */
/*   Updated: 2019/10/09 21:14:32 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		loadtextureobjs_minigun(t_doom *d, t_weapon *w)
{
	int	i = d->fps % w->frame_count; // TODO: delay
	d->img[w->images[w->state][i]];
}
