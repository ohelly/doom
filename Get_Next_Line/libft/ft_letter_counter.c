/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_letter_counter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:41:43 by lminta            #+#    #+#             */
/*   Updated: 2019/04/10 15:42:04 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_letter_counter(const char *str, char c)
{
	int	*letters;
	int	i;
	int words;

	words = ft_word_counter(str, c);
	i = 0;
	if (!(letters = (int*)malloc(sizeof(*letters) * words)))
		return (0);
	while (i < words)
	{
		letters[i] = 0;
		i++;
	}
	i = 0;
	while (*str == c)
		str++;
	while (*str)
	{
		if (*str != c)
			letters[i]++;
		if (*str == c && (*(str + 1) != c && *(str + 1) != 0))
			i++;
		str++;
	}
	return (letters);
}
