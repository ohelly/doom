/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_manipulations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:21:06 by njacobso          #+#    #+#             */
/*   Updated: 2019/10/29 01:50:30 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		rgb_multiply(int color, float value)
{
	int r;
	int g;
	int b;

	r = (color & 0xFF0000) * value;
	g = (color & 0x00FF00) * value;
	b = (color & 0x0000FF) * value;
	return ((r & 0xFF0000) | (g & 0x00FF00) | (b & 0x0000FF));
}

int		rgb_mix(int rgb1, int rgb2, float percent)
{
	float percent2;

	percent = CLAMP(percent, 0, 1);
	percent2 = 1 - percent;
	rgb1 = ((int)(((rgb1 >> 16) & 0xff) * percent +
				((rgb2 >> 16) & 0xff) * percent2) << 16) |
			((int)(((rgb1 >> 8) & 0xff) * percent +
				((rgb2 >> 8) & 0xff) * percent2) << 8) |
			((int)((rgb1 & 0xff) * percent +
				(rgb2 & 0xff) * percent2));
	return (rgb1);
}
