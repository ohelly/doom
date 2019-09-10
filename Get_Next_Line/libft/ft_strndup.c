/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 20:52:37 by lminta            #+#    #+#             */
/*   Updated: 2019/04/16 15:50:43 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	char	*copy;
	int		len;
	int		i;

	if (n > ft_strlen(src))
		len = n;
	else
		len = ft_strlen(src);
	if (!(copy = ft_strnew(len)))
		return (0);
	i = 0;
	while (i < len)
	{
		copy[i] = src[i];
		i++;
	}
	return (copy);
}
