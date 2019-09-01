/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:09:07 by ohelly            #+#    #+#             */
/*   Updated: 2018/11/30 16:06:57 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t c;

	c = size - 1;
	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	if (size <= ft_strlen(dst))
		return (size + ft_strlen(src));
	else if (size > ft_strlen(dst))
	{
		i = ft_strlen(src) + ft_strlen(dst);
		ft_strncat(dst, src, (c - ft_strlen(dst)));
	}
	return (i);
}
