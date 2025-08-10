/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 08:40:25 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/24 10:39:13 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t	ft_strlcpy(char *dest, const char *source, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (source[j] != '\0')
		j++;
	if (size == 0)
		return (j);
	while (source[i] != '\0' && i < size -1)
	{
		dest[i] = source[i];
		i++;
	}
	dest[i] = '\0';
	return (j);
}
