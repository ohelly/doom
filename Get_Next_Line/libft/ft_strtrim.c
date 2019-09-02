/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 16:53:15 by lminta            #+#    #+#             */
/*   Updated: 2019/04/09 17:32:03 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*trim;

	if (!s)
		return (0);
	len = ft_strlen(s);
	i = 0;
	while (s[i] != '\0' && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
		i++;
	while ((s[len - 1] == ' ' || s[len - 1] == '\t' ||
	s[len - 1] == '\n') && len > 0)
		len--;
	if (len)
		len -= i;
	if (!(trim = ft_strnew(len)))
		return (0);
	len += i;
	j = 0;
	while (i < len)
		trim[j++] = s[i++];
	return (trim);
}
