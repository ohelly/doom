/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 11:14:42 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/29 16:39:46 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int        check_extension(char *av)
{
    int		i;

    i = ft_strlen(av) - 4;
    if (!(ft_strcmp(&av[i], ".map")))
        return (1);
    return (0);
}

int		difficulty(t_doom *doom, char *av)
{
	if (ft_strequ(av, "Easy"))
		doom->difficult = 1;
	if (ft_strequ(av, "Medium"))
		doom->difficult = 2;
	if (ft_strequ(av, "Hard"))
		doom->difficult = 3;
	return (1);
}

int		validate_av(t_doom *doom, int ac, char **av)
{
	if (!(check_extension(av[0])))
		return (0);
	return (1);
}

int		load_level(t_doom *doom, char **av)
{
	if (!(load_all(doom, av)))
		return (0);
	return (1);
}

int		main(int ac, char **av)
{
	t_doom	*doom;

	if (ac < 2 || ac > 3)
		return (0);
	if (!(validate_av(doom, ac, &av[1])))
		return (0);
	if (!(doom = (t_doom*)ft_memalloc(sizeof(t_doom))))
		return (0);
		if (ac == 3)
	difficulty(doom, av[2]);
	doom->ac = ac;
	doom->av = av;
	if (!(doom->sdl = (t_sdl*)ft_memalloc(sizeof(t_sdl))))
		return (0);
	load_level(doom, av);
	return (0);
}
