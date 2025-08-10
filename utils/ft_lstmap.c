/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:08:50 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/24 10:37:59 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new;

	if (!lst)
		return (NULL);
	new = NULL;
	while (lst)
	{
		f(lst->content);
		new_list = ft_lstnew(lst->content);
		if (!lst)
		{
			del(lst->content);
			free(lst);
		}
		ft_lstadd_back(&new, new_list);
		lst = lst->next;
	}
	return (new);
}
