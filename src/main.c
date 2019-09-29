/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 11:14:42 by dtoy              #+#    #+#             */
/*   Updated: 2019/09/29 11:58:27 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		main()
{
	t_doom	*doom;
	
	if (!(doom = (t_doom*)ft_memalloc(sizeof(t_doom))))
		return (0);
	if (!(initall(doom)))
		return (0);
	if (!(loadall(doom)))
		return (0);
	loadtextures(doom);
	loadgame(doom);
	return (0);
}
