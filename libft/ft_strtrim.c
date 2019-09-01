/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 16:59:12 by ohelly            #+#    #+#             */
/*   Updated: 2018/12/06 20:54:45 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t			ft_max(char const *s)
{
	size_t i;

	i = ft_strlen(s) - 1;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t' || s[i] == '\0')
		i--;
	return (i);
}

char					*ft_strtrim(char const *s)
{
	size_t			i;
	unsigned int	j;
	char			*p;

	if (!s)
		return (0);
	j = 0;
	p = NULL;
	if (s[0] == '\0')
	{
		if (!(p = (char*)ft_memalloc(sizeof(char) * 1)))
			return (p = ft_memalloc(1));
		p[0] = '\0';
		return (p);
	}
	while (s[j] == ' ' || s[j] == '\n' || s[j] == '\t')
		j++;
	if (s[j] == '\0')
		return (p = ft_memalloc(1));
	i = ft_max(s);
	if (!(p = ft_strsub(s, j, (i - j) + 1)))
		return (p = ft_memalloc(1));
	return (p);
}
