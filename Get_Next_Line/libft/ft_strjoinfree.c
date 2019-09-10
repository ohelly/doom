/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 13:47:43 by lminta            #+#    #+#             */
/*   Updated: 2019/06/11 18:35:13 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinfree(char const *s1, char const *s2)
{
	char	*join;

	if (!s1 || !s2 || !(join = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (0);
	ft_strcpy(join, s1);
	ft_strcat(join, s2);
	free((void*)s1);
	free((void*)s2);
	return (join);
}
