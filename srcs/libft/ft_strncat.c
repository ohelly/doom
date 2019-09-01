/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 14:45:29 by ohelly            #+#    #+#             */
/*   Updated: 2018/12/10 13:30:46 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	int i;
	int c;

	i = 0;
	c = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	while (n != 0 && src[c] != '\0')
	{
		dest[i] = src[c];
		i++;
		c++;
		n--;
	}
	dest[i] = '\0';
	return (dest);
}
