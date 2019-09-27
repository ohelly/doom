/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:58:07 by dtoy              #+#    #+#             */
/*   Updated: 2019/09/19 15:26:56 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		loadsprites(t_xyzwh *spr_stock, char *str)
{
	static int	n = 0;
	int		j;
	int		t;
	
	t = 0;
	j = 0;
	while (j < ft_strlen(str))
	{
		if (ft_isdigit(str[j]) && t == 0)
		{
			spr_stock[n].y = atof(&str[j]);
			printf("spr y - %f\n", spr_stock[n].y);
			t = 1;
			while (ft_isdigit(str[j]))
				j++;
		}
		else if (ft_isdigit(str[j]) && t == 1)
		{
			spr_stock[n].x = atof(&str[j]);
			printf("spr x - %f\n", spr_stock[n].x);
			t = 2;
			while (ft_isdigit(str[j]))
				j++;
		}
		else if (ft_isdigit(str[j]) && t == 2)
		{
			spr_stock[n].text_ind = atoi(&str[j]);
			printf("spr text - %d\n", spr_stock[n].text_ind);
			t = 3;
			while (ft_isdigit(str[j]))
				j++;
		}
		else if (ft_isdigit(str[j]) && t == 3)
		{
			spr_stock[n].sector = atoi(&str[j]);
			printf("spr sector - %d\n", spr_stock[n].sector);
			while (ft_isdigit(str[j]))
				j++;
		}
		else
			j++;
		
	}
	n++;
	return (0);
}