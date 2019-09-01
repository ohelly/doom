/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 15:38:10 by ohelly            #+#    #+#             */
/*   Updated: 2018/12/06 20:55:05 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

static int				ft_words(char const *s, char c)
{
	int i;

	i = 0;
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		if (*s != '\0')
			i++;
		while (*s != c && *s != '\0')
			s++;
	}
	return (i);
}

static size_t			ft_len(const char *s, unsigned int ind, char c)
{
	size_t len;

	len = 0;
	while (s[ind] != c && s[ind] != '\0')
	{
		ind++;
		len++;
	}
	return (len);
}

static unsigned int		ft_ind(char const *s, unsigned int ind, char c)
{
	while (s[ind] == c)
		ind++;
	return (ind);
}

char					**ft_strsplit(char const *s, char c)
{
	int				words;
	char			**p;
	unsigned int	ind;
	int				mas;

	if (!s)
		return (0);
	p = NULL;
	ind = 0;
	mas = 0;
	words = ft_words(s, c);
	if (!(p = (char**)ft_memalloc(sizeof(char*) * words + 1)))
		return (p);
	while (mas <= words - 1)
	{
		ind = ft_ind(s, ind, c);
		if (!(p[mas++] = ft_strsub(s, ind, ft_len(s, ind, c))))
		{
			ft_strdel(p);
			return (NULL);
		}
		ind = ind + ft_len(s, ind, c) + 1;
	}
	p[mas] = NULL;
	return (p);
}
