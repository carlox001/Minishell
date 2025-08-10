/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:18:54 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/24 10:38:11 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				count;
	const unsigned char	*a;
	const unsigned char	*b;

	count = 0;
	a = (const unsigned char *) s1;
	b = (const unsigned char *) s2;
	if (n == 0)
		return (0);
	while (count < n - 1 && (a[count] == b[count]))
	{
		count++;
	}
	return (a[count] - b[count]);
}
