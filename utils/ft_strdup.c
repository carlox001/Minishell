/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:51:59 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/24 10:39:00 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strdup(const char *s)
{
	char	*rts;
	size_t	a;

	a = 0;
	rts = (char *)s;
	rts = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!rts)
		return (NULL);
	while (s[a] != '\0')
	{
		rts[a] = s[a];
		a++;
	}
	rts[a] = '\0';
	return (rts);
}
