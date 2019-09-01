/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 15:00:33 by ohelly            #+#    #+#             */
/*   Updated: 2018/12/02 15:32:05 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*p;

	p = NULL;
	i = 0;
	if (s)
	{
		if (!(p = (char*)malloc(sizeof(char) * (ft_strlen(s)) + 1)))
			return (p);
		while (s[i] != '\0')
		{
			p[i] = f(i, s[i]);
			i++;
		}
		p[i] = '\0';
	}
	return (p);
}
