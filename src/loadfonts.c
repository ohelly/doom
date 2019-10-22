/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadfonts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glormell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:05:50 by glormell          #+#    #+#             */
/*   Updated: 2019/10/22 19:34:09 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		loadfonts(t_hud *hud)
{
	return (!(hud->font = TTF_OpenFont("/Users/glormell/Library/Fonts/DooM.ttf",
			20)));
}
