/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_manipulations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:21:06 by njacobso          #+#    #+#             */
/*   Updated: 2019/10/23 17:21:15 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	rgb_multiply(int color, float value)
{
	int r;
	int g;
	int b;

	r = (color & 0xFF0000) * value;
	g = (color & 0x00FF00) * value;
	b = (color & 0x0000FF) * value;
	return ((r & 0xFF0000) | (g & 0x00FF00) | (b & 0x0000FF));
}
