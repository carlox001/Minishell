/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:10:57 by sfiorini          #+#    #+#             */
/*   Updated: 2025/02/03 17:04:47 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*new;

	if (lst)
	{
		while (*lst)
		{
			new = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = new;
		}
		lst = NULL;
	}
}
