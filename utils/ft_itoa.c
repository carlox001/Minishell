/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:55:33 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/24 10:37:39 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static size_t	ft_get_digits(int n)
{
	size_t	count;

	if (n == 0)
		return (1);
	count = 0;
	if (n < 0)
		n = -n;
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*rts;
	size_t	ndigit;
	size_t	m;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	m = (size_t)n;
	ndigit = ft_get_digits(n);
	if (n < 0)
	{
		m *= -1;
		ndigit++;
	}
	rts = (char *)malloc(sizeof(char) * (ndigit + 1));
	if (rts == NULL)
		return (NULL);
	rts[ndigit] = 0;
	while (ndigit--)
	{
		rts[ndigit] = m % 10 + '0';
		m = m / 10;
	}
	if (n < 0)
		rts[0] = '-';
	return (rts);
}
