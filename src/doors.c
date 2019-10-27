/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 19:21:38 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/27 19:21:48 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	close_door(t_sectors *s, t_fps fps)
{
	s->ceil -= fps.time_frame * 120.f;
	if (s->ceil <= s->floor)
	{
		s->ceil = s->floor;
		s->active = 0;
		s->open = 0;
		s->close = 1;
	}
}

void	open_door(t_sectors *s, t_fps fps)
{
	s->ceil += fps.time_frame * 120.f;
	if (s->ceil >= s->constceil)
	{
		s->ceil = s->constceil;
		s->active = 0;
		s->open = 1;
		s->close = 0;
	}
}

int		open_door_timer(t_sectors *s, t_fps fps)
{
	static float t = 0;

	if (s->open)
	{
		t += fps.time_frame;
		if (t >= 1.5f)
		{
			t = 0;
			return (1);
		}
	}
	return (0);
}

int		doors(t_doom *doom, t_player player, t_fps fps)
{
	int			j;
	int			a;
	t_sectors	*s;

	j = 0;
	a = 0;
	while (j < doom->num.sectors)
	{
		s = &doom->sectors[j];
		if ((open_door_timer(s, fps)))
			a = 1;
		if (s->open && a == 1)
			s->active = 1;
		if (s->active && j == player.sector && s->open)
			return (0);
		if ((s->type == 1 || (s->type == 2 && player.key))
		&& s->active && s->open)
			close_door(s, fps);
		else if ((s->type == 1 || (s->type == 2 && player.key))
		&& s->active && s->close)
			open_door(s, fps);
		j++;
	}
	return (0);
}
