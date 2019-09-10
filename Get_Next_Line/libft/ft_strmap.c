/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 12:30:23 by lminta            #+#    #+#             */
/*   Updated: 2019/04/09 18:43:53 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*map;
	size_t	i;

	i = 0;
	if (!s || !(map = ft_strnew(ft_strlen(s))) || !f)
		return (0);
	while (s[i])
	{
		map[i] = f(s[i]);
		i++;
	}
	return (map);
}
