/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 18:08:24 by ohelly            #+#    #+#             */
/*   Updated: 2018/12/10 14:49:43 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*list;
	t_list	*link;

	if (!lst)
		return (0);
	if (!(link = malloc(sizeof(t_list))))
		return (NULL);
	link = f(lst);
	list = link;
	while (lst->next)
	{
		lst = lst->next;
		link->next = ft_lstnew(f(lst)->content, f(lst)->content_size);
		if (link->next == NULL)
		{
			free(link);
			return (NULL);
		}
		link = link->next;
	}
	return (list);
}
