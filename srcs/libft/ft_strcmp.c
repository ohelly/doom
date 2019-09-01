/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 18:54:50 by ohelly            #+#    #+#             */
/*   Updated: 2018/11/27 17:46:42 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(const char *s1, const char *s2)
{
	int				i;
	unsigned char	*p;
	unsigned char	*l;

	p = ((unsigned char*)s1);
	l = ((unsigned char*)s2);
	i = 0;
	while (p[i] != '\0' || l[i] != '\0')
	{
		if (p[i] != l[i])
			return (p[i] - l[i]);
		i++;
	}
	return (0);
}
