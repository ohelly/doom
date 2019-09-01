/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 13:00:19 by ohelly            #+#    #+#             */
/*   Updated: 2018/12/11 15:58:39 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list *nexte;
	t_list *dele;

	if (!*alst)
		return ;
	nexte = *alst;
	while (nexte)
	{
		dele = nexte->next;
		del(nexte->content, nexte->content_size);
		free(nexte);
		nexte = dele;
	}
	*alst = 0;
}
