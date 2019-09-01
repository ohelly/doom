/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 15:52:58 by ohelly            #+#    #+#             */
/*   Updated: 2018/12/10 13:26:31 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char *pd;
	unsigned char *ps;

	pd = (unsigned char*)dest;
	ps = (unsigned char*)src;
	if (pd <= ps || pd >= (ps + n))
	{
		while (n--)
			*pd++ = *ps++;
	}
	else
	{
		pd = pd + n - 1;
		ps = ps + n - 1;
		while (n--)
			*pd-- = *ps--;
	}
	return (dest);
}
