/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 19:01:45 by ohelly            #+#    #+#             */
/*   Updated: 2018/12/11 16:22:22 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	while (!*s2)
		return ((char*)s1);
	if (n >= ft_strlen(s1))
		return (ft_strstr(s1, s2));
	while (ft_strlen(s2) <= n)
	{
		if (ft_strncmp(s1, s2, ft_strlen(s2)) == 0)
			return ((char*)s1);
		s1++;
		n--;
	}
	return (0);
}
