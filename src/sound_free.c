/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 00:45:44 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/29 00:45:54 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		sound_free_everything(t_doom *doom)
{
	int i;

	i = -1;
	while (++i < 2)
		Mix_FreeMusic(doom->music[i].music);
	i = -1;
	while (++i < 17)
		Mix_FreeChunk(doom->sound[i].sound);
	return (1);
}
