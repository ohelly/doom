/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_counter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:43:08 by lminta            #+#    #+#             */
/*   Updated: 2019/06/11 19:18:00 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_word_counter(const char *str, char c)
{
	int		words;

	words = 0;
	if (*str != c)
		words++;
	while (*str)
	{
		if (*str == c && (*(str + 1) != c && *(str + 1) != 0))
			words++;
		str++;
	}
	return (words);
}
