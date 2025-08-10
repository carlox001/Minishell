/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:33:49 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/24 10:39:39 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*rts;
	size_t	count;
	size_t	nel;

	if (!s)
		return (NULL);
	count = 0;
	nel = 0;
	rts = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!rts)
		return (NULL);
	while (s[count] != '\0')
	{
		if (nel < len && start <= count)
		{
			rts[nel] = s[count];
			nel++;
		}
		count++;
	}
	rts[nel] = '\0';
	return (rts);
}
