/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 20:22:31 by ohelly            #+#    #+#             */
/*   Updated: 2018/12/10 13:32:02 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	char	*p;
	int		i;
	int		c;

	i = 0;
	c = 0;
	while (s2[i] != '\0')
		i++;
	if (i == 0)
		return (((char*)s1));
	p = NULL;
	while (s1[c] != '\0')
	{
		if ((ft_strncmp(&s1[c], s2, i)) == 0)
		{
			p = ((char*)s1 + c);
			return (p);
		}
		c++;
	}
	return (p);
}
