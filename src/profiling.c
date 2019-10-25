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

int		profile_output(t_doom *doom)
{
	printf("===Profiling results===\n");
	printf("Frametime: %f ms\n", doom->fps.time_frame);
	printf("FPS is %f\n", 1 / doom->fps.time_frame);
	printf("Average FPS is %f\n", 1 /
			(doom->fps.fps_total / doom->fps.fps_count));
	doom->fps.fps_count = 0;
	doom->fps.fps_total = 0;
	printf("===Profiling completed===\n");
	return (1);
}
