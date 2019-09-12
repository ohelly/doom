/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:59:21 by lminta            #+#    #+#             */
/*   Updated: 2019/06/03 17:01:07 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	itoa(const char c, int base)
{
	if (ft_isdigit(c))
		return (c - '0' < base ? c - '0' : -1);
	else if (ft_islower(c))
		return (c - 'a' + 10 < base ? c - 'a' + 10 : -1);
	else if (ft_isupper(c))
		return (c - 'A' + 10 < base ? c - 'A' + 10 : -1);
	else
		return (-1);
}

int			ft_atoi_base(const char *str, int base)
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
	while (*str && itoa(*str, base) != -1)
	{
		if (integer > 0 && integer * base + sign * itoa(*str, base) < 0)
			return (-1);
		if (integer < 0 && integer * base + sign * itoa(*str, base) > 0)
			return (0);
		integer = integer * base + sign * itoa(*str, base);
		str++;
	}
	return ((int)integer);
}
