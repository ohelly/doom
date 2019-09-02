/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 20:41:11 by dtoy              #+#    #+#             */
/*   Updated: 2019/09/01 17:44:54 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void     draw(t_sdl *sdl, t_line *line)
{
    if (line->y0 >= 0 && line->y0 < HEIGHT && line->x0 >= 0 && line->x0 < WIDTH)
        sdl->pix[line->y0 * WIDTH + line->x0] = sdl->line->color;
}

static int      ft_ifmin(int length, t_sdl *sdl, int lengthx, int lengthy)
{
    int d;
    d = -lengthx;
    while (--length)
    {
        draw(sdl, sdl->line);
        sdl->line->x0 += sdl->line->dx;
        d += 2 * lengthy;
        if (d > 0)
        {
            d -= 2 * lengthx;
            sdl->line->y0 += sdl->line->dy;
        }
    }
    return (0);
}

static int      ft_ifmax(int length, t_sdl *sdl, int lengthx, int lengthy)
{
    int d;
    d = -lengthy;
    while (--length)
    {
        draw(sdl, sdl->line);
        sdl->line->y0 += sdl->line->dy;
        d += 2 * lengthx;
        if (d > 0)
        {
            d -= 2 * lengthy;
            sdl->line->x0 += sdl->line->dx;
        }
    }
    return (0);
}

int             line(t_sdl *sdl)
{
    int lengthx;
    int lengthy;
    int length;

    lengthx = abs(sdl->line->x1 - sdl->line->x0);
    lengthy = abs(sdl->line->y1 - sdl->line->y0);
    length = fmax(lengthx, lengthy);
    sdl->line->dx = (sdl->line->x1 - sdl->line->x0 >= 0 ? 1 : -1);
    sdl->line->dy = (sdl->line->y1 - sdl->line->y0 >= 0 ? 1 : -1);
    if (length == 0)
        draw(sdl, sdl->line);
    if (lengthy <= lengthx)
        ft_ifmin(++length, sdl, lengthx, lengthy);
    else
        ft_ifmax(++length, sdl, lengthx, lengthy);
    return (0);
}