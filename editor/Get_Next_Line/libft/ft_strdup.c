/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 20:52:37 by lminta            #+#    #+#             */
/*   Updated: 2019/04/16 15:46:44 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*copy;
	int		len;

	len = ft_strlen(src);
	if (!(copy = ft_strnew(len)))
		return (0);
	while (len >= 0)
	{
		*(copy + len) = *(src + len);
		len--;
	}
	return (copy);
}
