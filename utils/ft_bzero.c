/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 08:36:42 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/24 10:36:58 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			count;
	unsigned char	*a;

	count = 0;
	a = (unsigned char *) s;
	while (count < n)
	{
		a[count] = 0;
		count++;
	}
}
