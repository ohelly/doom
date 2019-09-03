/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 14:51:11 by lminta            #+#    #+#             */
/*   Updated: 2019/04/07 16:30:21 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	unsigned int	i;
	unsigned int	len;
	char			*str;

	len = 0;
	while (n / ft_pow(10, len) / 10 != 0)
		len++;
	len++;
	if (n < 0)
		len++;
	if (!(str = ft_strnew(len)))
		return (0);
	if (n == 0)
		str[0] = '0';
	if (n < 0)
		str[0] = '-';
	i = 0;
	while (n != 0)
	{
		str[len - 1 - i] = ft_abs(n % 10) + '0';
		i++;
		n = n / 10;
	}
	return (str);
}
