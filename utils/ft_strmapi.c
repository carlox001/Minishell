/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:23:18 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/24 10:39:21 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*rts;
	size_t	i;
	size_t	count;

	i = 0;
	count = ft_strlen(s);
	if (!s)
		return (NULL);
	rts = (char *)malloc(sizeof(char) * (count + 1));
	if (!s)
		return (NULL);
	while (i < count)
	{
		rts[i] = f(i, s[i]);
		i++;
	}
	rts[i] = '\0';
	return (rts);
}
