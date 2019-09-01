/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 16:55:14 by ohelly            #+#    #+#             */
/*   Updated: 2018/11/30 17:28:39 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	size_t	i;
	char	*p;

	p = NULL;
	i = 0;
	if (!(p = (char*)malloc(sizeof(char) * size + 1)))
		return (p);
	while (i <= size)
	{
		p[i] = '\0';
		i++;
	}
	return (p);
}
