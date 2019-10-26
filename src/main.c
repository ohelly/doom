/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 11:14:42 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/21 14:26:39 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		main()
{
	t_doom	*doom;

	if (!(doom = (t_doom*)ft_memalloc(sizeof(t_doom))))
		return (0);
		
	if (!(initall(doom)))
		return (0);
	
	if (!(loadall(doom)))
		return (0);
	printf("Textures loaded.\n");
	//loadtextures(doom);
	//&doom->img[doom->walls[s->txtw[doom->cood.n]].image];
	//int		t;
	//t = doom->sectors[0].txtw[0];
	//printf("t - %d\n", t);
	//printf("i - %d\n", doom->walls[t].image);
	//printf("ind - %d\n", doom->img[doom->walls[t].image]);
	load_game(doom);
	//printf("Game loaded.\n");
	return (0);
}
