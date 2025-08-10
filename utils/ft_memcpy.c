/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:09:06 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/24 10:38:13 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char			*a;
	const unsigned char		*b;
	size_t					count;

	a = (unsigned char *) dest;
	b = (const unsigned char *) src;
	count = 0;
	if (!dest && !src)
		return (NULL);
	while (count < n)
	{
		a[count] = b[count];
		count++;
	}
	return (dest);
}
