/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 14:45:50 by ohelly            #+#    #+#             */
/*   Updated: 2018/12/10 13:29:39 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	int i;

	i = 0;
	while (n != 0 && src[i] != '\0')
	{
		dest[i] = src[i];
		n--;
		i++;
	}
	while (n != 0)
	{
		dest[i] = '\0';
		i++;
		n--;
	}
	return (dest);
}
