/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 17:57:29 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/13 16:06:22 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

int			die_msg(char *msg)
{
	ft_putendl(msg);
	exit(0);
	return (0);
}

int			puts_error(int err)
{
	if (err == 1)
		return (die_msg("Usage [.map] file"));
	if (err == 2)
		return (die_msg("Not a valid map"));
	if (err == 3)
		return (die_msg("Failed to read map"));
	return (0);
}

int			main(int ac, char **av)
{
	t_doom		*doom;
	int			err;

	if (ac == 1)
		return (die_msg("Usage [.map] file"));
	if (ac > 2)
		return (die_msg("Too many arguments"));
	if (!(doom = (t_doom*)ft_memalloc(sizeof(t_doom))))
		return (die_msg("Failed to allocate doom struct"));
	if (!(sdl_init(doom)))
		return (die_msg("Failed to init doom"));
	err = load_map(av[1], doom);
	if (err != 0)
		return (puts_error(err));
	while (1)
		key_and_mouse_press(doom);
	return (0);
}
