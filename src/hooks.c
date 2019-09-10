/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 19:33:22 by dtoy              #+#    #+#             */
/*   Updated: 2019/09/02 14:59:05 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			hooks(t_doom *doom, SDL_Event ev)
{
	(void) doom;
	if (ev.type == SDL_KEYDOWN)
	{
		if (ev.key.keysym.sym == '\033')
		{
		 	SDL_Quit();
			exit(0);
		}
	}
	return (0);
}
