/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:35:25 by dtoy              #+#    #+#             */
/*   Updated: 2019/09/02 15:19:01 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int     main()
{
	t_doom  *doom;

	if (!(doom = ft_memalloc(sizeof(t_doom))))
		return (0);
	if (!(doom->sdl = ft_memalloc(sizeof(t_sdl))))
		return (0);
	if (!(doom->sdl->line = ft_memalloc(sizeof(t_line))))
		return (0);
	loadmap(doom);
	sdlstart(doom);
	return (0);
}
