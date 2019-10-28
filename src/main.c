/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 11:14:42 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/27 16:52:37 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		main(int ac, char **av)
{
	t_doom	*doom;

	if (ac < 2)
		return (0);
	if (!(doom = (t_doom*)ft_memalloc(sizeof(t_doom))))
		return (0);
	if (!(doom->sdl = (t_sdl*)ft_memalloc(sizeof(t_sdl))))
		return (0);
	ft_putendl("Loading map.");
	if (!(load_all(doom, av)))
		return (0);
	printf("All loaded.\n");
	load_game(doom);
	return (0);
}
