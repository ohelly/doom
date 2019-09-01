/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 15:48:29 by ohelly            #+#    #+#             */
/*   Updated: 2019/01/16 17:26:55 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(const char *s1, char const *s2)
{
	size_t			c;
	char			*p;

	if (!s1 || !s2)
		return (0);
	c = ft_strlen(s1) + ft_strlen(s2);
	if (!(p = (char*)ft_memalloc(sizeof(char) * c + 1)))
		return (0);
	ft_strcat(p, s1);
	ft_strcat(p, s2);
	return (p);
}
