/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:59:21 by lminta            #+#    #+#             */
/*   Updated: 2019/04/11 18:24:13 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	long int	integer;
	int			sign;

	integer = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		if (integer > 0 && integer * 10 + sign * (*str - '0') < 0)
			return (-1);
		if (integer < 0 && integer * 10 + sign * (*str - '0') > 0)
			return (0);
		integer = integer * 10 + sign * (*str - '0');
		str++;
	}
	return ((int)integer);
}
