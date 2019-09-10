/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:48:13 by lminta            #+#    #+#             */
/*   Updated: 2019/04/09 17:53:07 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	int				i;
	unsigned int	mod_nb;

	i = 1;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		mod_nb = (-1) * nb;
	}
	else
		mod_nb = nb;
	while (mod_nb / i / 10 > 0)
		i = i * 10;
	while (i >= 1)
	{
		ft_putchar_fd(mod_nb / i % 10 + '0', fd);
		i = i / 10;
	}
}
