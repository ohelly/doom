/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:25:35 by ohelly            #+#    #+#             */
/*   Updated: 2018/12/10 13:26:51 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *arr, int c, size_t n)
{
	unsigned char	*p;
	int				i;

	p = NULL;
	i = 0;
	while (n-- != 0)
	{
		if (*((unsigned char*)arr + i) == ((unsigned char)c))
		{
			p = ((unsigned char*)arr + i);
			return (p);
		}
		i++;
	}
	return (p);
}
