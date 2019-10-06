/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_press.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 15:16:30 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/06 15:49:41 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void		mouse_press(t_doom *doom, int x, int y)
{
	if (x >= 950 && x <= 1000 &&
	y >= 10 && y <= 60)
	{
		if (doom->sects->selected_sector == 0)
			doom->sects->selected_sector = doom->sects->count;
		doom->sects->selected_sector--;
	}
	else if (x >= 1200 && x <= 1250 &&
	y >= 10 && y <= 60)
	{
		if (doom->sects->selected_sector == doom->sects->count - 1)
			doom->sects->selected_sector = -1;
		doom->sects->selected_sector++;
	}
}