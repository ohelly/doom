/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:04:31 by lminta            #+#    #+#             */
/*   Updated: 2019/04/10 19:36:34 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	malsplit(char **split, int letters, int i)
{
	int j;

	j = 0;
	if (!(split[i] = ft_strnew(letters)))
	{
		while (j < i)
		{
			ft_memdel((void **)(&split[j]));
			j++;
		}
		ft_memdel((void **)split);
		return (0);
	}
	return (1);
}

static char	**ft_split(int *letters, char **split, const char *str, char c)
{
	int		i;
	int		j;
	int		k;
	char	*cut;

	j = 0;
	i = 0;
	k = 0;
	if (!(cut = ft_cut(str, c)))
		return (0);
	while (i < ft_word_counter(str, c))
	{
		j = 0;
		while (j < letters[i])
		{
			split[i][j] = *(cut + k);
			k++;
			j++;
		}
		split[i][j] = '\0';
		i++;
	}
	split[i] = 0;
	return (split);
}

char		**ft_strsplit(const char *str, char c)
{
	char	**split;
	int		i;
	int		*letters;

	if (!ft_cut(str, c) || *str == 0 || *ft_cut(str, c) == 0)
	{
		if (!(split = (char**)malloc(sizeof(char*))))
			return (0);
		split[0] = 0;
	}
	else
	{
		i = 0;
		if (!(letters = ft_letter_counter(str, c)) ||
!(split = (char**)malloc(sizeof(char*) * (ft_word_counter(str, c) + 1))))
			return (0);
		while (i < ft_word_counter(str, c))
		{
			if (!malsplit(split, letters[i], i))
				return (0);
			i++;
		}
		ft_split(letters, split, str, c);
	}
	return (split);
}
