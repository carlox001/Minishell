/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:48:25 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/24 10:37:09 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*bezero;
	size_t			b;
	size_t			n;
	void			*a;

	b = 0;
	n = (nmemb * size);
	a = malloc(n);
	if (a == NULL)
		return (NULL);
	bezero = (unsigned char *)a;
	while (b < n)
	{
		bezero[b] = 0;
		b++;
	}
	return (a);
}
