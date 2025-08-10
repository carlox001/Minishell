/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:56:20 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/24 10:38:24 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned long	count;
	unsigned char	*a;

	count = 0;
	a = (unsigned char *)s;
	while (count < n)
	{
		a[count] = (unsigned char)c;
		count++;
	}
	return (s);
}
