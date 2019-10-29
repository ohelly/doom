/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadfonts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:05:50 by glormell          #+#    #+#             */
/*   Updated: 2019/10/29 16:53:36 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			load_fonts(t_doom *doom)
{
	char	*env;
	char	*doom_f;

	env = ft_strjoin(getenv("HOME"), "/Documents/DoomNukem");
	doom_f = ft_strjoinc(env, "/DooM.ttf");
	doom->hud->font = TTF_OpenFont(doom_f, 20);
	doom->menu.font = TTF_OpenFont(doom_f, 14);
	free(env);
	free(doom_f);
	return (1);
}
