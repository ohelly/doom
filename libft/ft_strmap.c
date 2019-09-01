/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 14:44:38 by ohelly            #+#    #+#             */
/*   Updated: 2018/12/07 17:49:48 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	unsigned int	i;
	char			*p;

	i = 0;
	p = NULL;
	if (s)
	{
		if (!(p = (char*)malloc(sizeof(char) * (ft_strlen(s)) + 1)))
			return (p);
		while (s[i] != '\0')
		{
			p[i] = f(s[i]);
			i++;
		}
		p[i] = '\0';
	}
	return (p);
}
