/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:27:27 by lminta            #+#    #+#             */
/*   Updated: 2019/04/09 18:06:05 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *head;

	if (!(head = (t_list*)malloc(sizeof(t_list))))
		return (0);
	if (content)
	{
		head->content_size = content_size;
		if (!(head->content = (void *)malloc(content_size)))
			return (0);
		head->content = ft_memcpy(head->content, content, content_size);
	}
	else
	{
		head->content_size = 0;
		head->content = NULL;
	}
	head->next = NULL;
	return (head);
}
