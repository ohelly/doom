/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:38:53 by lminta            #+#    #+#             */
/*   Updated: 2019/04/10 15:40:06 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_cut(const char *str, char c)
{
	char	*cut;
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (!str)
		return (0);
	while (*(str + i))
	{
		if (*(str + i) != c)
			len++;
		i++;
	}
	if (!(cut = (char*)malloc(sizeof(*cut) * (len + 1))))
		return (0);
	i = 0;
	while (*(str))
	{
		if (*str != c)
			*(cut + i++) = *str;
		str++;
	}
	*(cut + i) = '\0';
	return (cut);
}
