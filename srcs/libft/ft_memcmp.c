/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 18:06:01 by ohelly            #+#    #+#             */
/*   Updated: 2018/12/10 13:27:19 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int	i;

	i = 0;
	while (n-- != 0)
	{
		if (*((unsigned char*)s1 + i) != *((unsigned char*)s2 + i))
			return ((*((unsigned char*)s1 + i)) - (*((unsigned char*)s2 + i)));
		i++;
	}
	return (0);
}
