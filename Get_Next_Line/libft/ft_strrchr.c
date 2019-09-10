/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 17:09:16 by lminta            #+#    #+#             */
/*   Updated: 2019/04/07 11:55:14 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = -1;
	while (s[i])
	{
		if (s[i] == (char)c)
			tmp = i;
		i++;
	}
	if (s[i] == (char)c)
		tmp = i;
	if (tmp == -1)
		return (0);
	return ((char *)s + tmp);
}
