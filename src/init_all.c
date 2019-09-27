/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:17:32 by dtoy              #+#    #+#             */
/*   Updated: 2019/09/24 08:39:53 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int     init_all(t_doom *doom)
{
	if (!(doom->sdl = (t_sdl*)ft_memalloc(sizeof(t_sdl))))
       return (0);
	if (!(doom->sdl->line = (t_line*)ft_memalloc(sizeof(t_line))))
        return (0);
	if (!(doom->textures = (t_textures*)ft_memalloc(sizeof(t_textures))))
        return (0);
    return (0);
}
