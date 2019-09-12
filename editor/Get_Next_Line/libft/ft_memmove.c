/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 21:27:15 by lminta            #+#    #+#             */
/*   Updated: 2019/04/14 14:07:11 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (src == dst)
		return (dst);
	if (src > dst)
		ft_memcpy(dst, src, len);
	else
	{
		i = 1;
		while ((int)(len - i) >= 0)
		{
			((char *)dst)[len - i] = ((char *)src)[len - i];
			i++;
		}
	}
	return (dst);
}
