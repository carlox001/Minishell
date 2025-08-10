/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 08:52:04 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/24 10:39:35 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

//caratteri da saltare dall`inizio
static int	ft_start(char const *rts, char const *tes)
{
	int	l;
	int	m;
	int	value;

	l = 0;
	m = 0;
	value = 0;
	while (rts[l] != '\0')
	{
		while (tes[m] != '\0')
		{
			if (rts[l] == tes[m])
			{
				value++;
				m = 0;
				break ;
			}
			m++;
		}
		l++;
	}
	return (value);
}
//caratteri da saltare dalla fine

static int	ft_finish(const char *rts, const char *tes)
{
	int	l;
	int	m;
	int	value;

	l = ft_strlen(rts) - 1;
	m = 0;
	value = 0;
	while (l >= 0)
	{
		while (tes[m] != '\0')
		{
			if (rts[l] == tes[m])
			{
				value++;
				m = 0;
				break ;
			}
			m++;
		}
		l--;
	}
	return (value);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*a;
	size_t	front;
	size_t	back;
	size_t	b;

	if (!s1)
		return (NULL);
	front = ft_start(s1, set);
	back = ft_strlen(s1) - ft_finish(s1, set);
	a = (char *)malloc(sizeof(char) * (back + 1));
	if (!a)
		return (NULL);
	b = 0;
	while (front < back)
	{
		a[b] = s1[front];
		b++;
		front++;
	}
	a[b] = '\0';
	return (a);
}
