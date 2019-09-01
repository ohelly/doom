/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 15:57:22 by ohelly            #+#    #+#             */
/*   Updated: 2018/12/10 13:25:04 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char*)(dest + i) = *(unsigned char*)(src + i);
		if (*((unsigned char*)src + i) == ((unsigned char)c))
			return ((unsigned char*)dest + (i + 1));
		i++;
	}
	return (NULL);
}
