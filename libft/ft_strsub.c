/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 15:35:16 by ohelly            #+#    #+#             */
/*   Updated: 2019/01/17 16:31:28 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*p;

	i = 0;
	p = NULL;
	if (s)
	{
		if (!(p = (char*)ft_memalloc(sizeof(char) * len + 1)))
			return (p);
		while (i < len)
		{
			p[i] = s[start];
			i++;
			start++;
		}
		p[i] = '\0';
	}
	return (p);
}
