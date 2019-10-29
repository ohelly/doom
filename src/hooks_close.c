/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 19:52:30 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/28 19:52:55 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	close_program(SDL_Event ev, t_doom *doom)
{
	if (ev.key.keysym.sym == '\033')
	{
		sound_free_everything(doom);
		Mix_Quit();
		SDL_Quit();
		exit(0);
	}
}
