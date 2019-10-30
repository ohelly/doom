/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadpics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 13:47:25 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/29 17:41:32 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		findvx(t_xy *v1, t_xy *v2, t_xy *vert, int wall)
{
	v1->x = vert[wall].x;
	v1->y = vert[wall].y;
	v2->x = vert[wall + 1].x;
	v2->y = vert[wall + 1].y;
	return (0);
}

int		takencount(char *str)
{
	int		j;
	int		count;

	j = 0;
	count = 0;
	while (str[j])
	{
		if (ft_isdigit(str[j]) || str[j] == '-')
		{
			count++;
			while (ft_isdigit(str[j]) || str[j] == '-')
				j++;
		}
		else
			j++;
	}
	return (count);
}

int		player_win(t_doom *doom)
{
	doom->player.f_col = 0x0000ff;
	doom->player.f_dur = 2.0f;
	doom->player.won = 1;
	return (1);
}
