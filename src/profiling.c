/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   profiling.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:35:24 by njacobso          #+#    #+#             */
/*   Updated: 2019/10/23 17:36:02 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
**	printf("Frametime: %f ms\n", doom->fps.time_frame);
**	printf("FPS is %f\n", 1 / doom->fps.time_frame);
**	printf("Average FPS is %f\n", 1 /
**			(doom->fps.fps_total / doom->fps.fps_count));
*/

int		profile_output(t_doom *doom)
{
	ft_putendl("===Profiling results===");
	doom->fps.fps_count = 0;
	doom->fps.fps_total = 0;
	ft_putendl("===Profiling completed===");
	return (1);
}
