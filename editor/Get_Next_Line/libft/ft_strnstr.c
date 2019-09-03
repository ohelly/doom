/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 15:24:52 by lminta            #+#    #+#             */
/*   Updated: 2019/04/07 11:55:05 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	unsigned int i;
	unsigned int j;
	unsigned int k;

	i = 0;
	if (*to_find == '\0')
		return ((char *)str);
	while (str[i] && i < len)
	{
		if (str[i] == *to_find)
		{
			j = 0;
			k = i;
			while ((str[k] == to_find[j]) && to_find[j] && k < len)
			{
				k++;
				j++;
			}
			if (to_find[j] == 0)
				return ((char *)str + i);
		}
		i++;
	}
	return (0);
}
