/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 18:34:51 by ohelly            #+#    #+#             */
/*   Updated: 2018/12/04 16:55:39 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	int				c;
	unsigned char	*p;
	unsigned char	*l;

	i = 1;
	c = 0;
	p = ((unsigned char*)s1);
	l = ((unsigned char*)s2);
	while ((i <= n) && ((p[c] != '\0') || (l[c] != '\0')))
	{
		if (p[c] != l[c])
			return (p[c] - l[c]);
		c++;
		i++;
	}
	return (0);
}
