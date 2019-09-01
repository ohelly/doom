/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 16:35:00 by ohelly            #+#    #+#             */
/*   Updated: 2018/12/07 19:32:04 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void		ft_lstdelone(t_list **alst, void (*del)(void*, size_t))
{
	if (!*alst)
		return ;
	del((*alst)->content, (*alst)->content_size);
	ft_memdel((void**)alst);
}
