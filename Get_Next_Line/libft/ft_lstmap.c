/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:01:41 by lminta            #+#    #+#             */
/*   Updated: 2019/04/09 14:23:57 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *head;

	head = NULL;
	if (lst)
	{
		if (!(head = (t_list *)malloc(sizeof(t_list))))
			return (NULL);
		head = f(lst);
		head->next = ft_lstmap(lst->next, f);
	}
	return (head);
}
