/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recharlloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 16:12:48 by lminta            #+#    #+#             */
/*   Updated: 2019/04/25 16:50:09 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_recharlloc(char **str, char c)
{
	char		*buff;
	size_t		len;

	len = ft_strlen(*str);
	if (!(buff = ft_strnew(len + 1)))
		return (0);
	if (*str)
		ft_memcpy(buff, *str, len);
	buff[len] = c;
	if (*str)
		ft_memdel((void **)str);
	return (buff);
}
