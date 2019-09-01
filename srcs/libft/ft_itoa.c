/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 16:50:06 by ohelly            #+#    #+#             */
/*   Updated: 2018/12/06 20:54:26 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_zero(int n)
{
	char	*p;

	p = NULL;
	if (!(p = (char*)ft_memalloc(sizeof(char) * 2)))
		return (p);
	p[0] = '0' + n % 10;
	p[1] = '\0';
	return (p);
}

static int		ft_count(int n)
{
	int		count;

	count = 0;
	if (n < 0)
		count++;
	while (n != 0)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

static char		*ft_ifminint(int n)
{
	char	*p;
	int		count;

	p = NULL;
	count = ft_count(n);
	if (!(p = (char*)ft_memalloc(sizeof(char) * count + 1)))
		return (p);
	p[count--] = '\0';
	p[count--] = '8';
	n = n / 10;
	n = n * (-1);
	p[0] = '-';
	while (n != 0)
	{
		p[count--] = '0' + n % 10;
		n = n / 10;
	}
	return (p);
}

char			*ft_itoa(int n)
{
	int		count;
	char	*p;
	int		i;

	p = NULL;
	if (n == 0)
		return (ft_zero(n));
	if (n == -2147483648)
		return (ft_ifminint(n));
	i = n;
	count = ft_count(n);
	if (!(p = (char*)ft_memalloc(sizeof(char) * count + 1)))
		return (p);
	p[count--] = '\0';
	if (i < 0)
	{
		p[0] = '-';
		i = i * (-1);
	}
	while (i != 0)
	{
		p[count--] = '0' + i % 10;
		i = i / 10;
	}
	return (p);
}
