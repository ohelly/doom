/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawscope.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:12:34 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/27 21:07:47 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		vertical_line(int *pix)
{
	int		y;
	int		x;
	int		len;
	int		w;

	len = 15;
	w = 2;
	x = WIDTH / 2 - w;
	while (x < WIDTH / 2 + w)
	{
		y = HEIGHT / 2 - len;
		while (y < HEIGHT / 2 + len)
		{
			pix[y * WIDTH + x] = 0xFFFFFF;
			y++;
		}
		x++;
	}
}

void		horizontal_line(int *pix)
{
	int		y;
	int		x;
	int		len;
	int		w;

	len = 15;
	w = 2;
	x = WIDTH / 2 - len;
	while (x < WIDTH / 2 + len)
	{
		y = HEIGHT / 2 - w;
		while (y < HEIGHT / 2 + w)
		{
			pix[y * WIDTH + x] = 0xFFFFFF;
			y++;
		}
		x++;
	}
}

void		draw_scope(t_sdl *sdl)
{
	vertical_line(sdl->pix);
	horizontal_line(sdl->pix);
}
