/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadfonts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:05:50 by glormell          #+#    #+#             */
/*   Updated: 2019/10/30 20:01:34 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		close_fonts(t_doom *doom)
{
	TTF_CloseFont(doom->hud->font);
	TTF_CloseFont(doom->menu.font);
}

int			load_fonts(t_doom *doom)
{
	char	*env;
	char	*doom_f;

	printf("load_fonts\n");
	env = ft_strjoin(getenv("HOME"), "/Documents/DoomNukem");
	doom_f = ft_strjoinc(env, "/DooM.ttf");
	doom->hud->font = TTF_OpenFont(doom_f, 20);
	doom->menu.font = TTF_OpenFont(doom_f, 14);
	free(doom_f);
	printf("load_fonts\n");
	return (1);
}
