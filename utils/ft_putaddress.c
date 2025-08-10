/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddress.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:23:26 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/24 10:38:34 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// void *xcalloc(size_t n, size_t x)
// {
// 	(void)n;
// 	(void)x;
// 	return NULL;
// }

int	ft_putaddress_check(unsigned long long nb)
{
	if (!nb)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	return (ft_putaddress(nb));
}

static int	ft_hexlen(unsigned long long nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb /= 16;
		len++;
	}
	return (len);
}

int	ft_putaddress(unsigned long long nb)
{
	int					i;
	char				*base;
	char				*temp;
	unsigned long long	result;

	result = nb;
	i = ft_hexlen(nb) - 1;
	temp = (char *)ft_calloc(i + 1, sizeof(char));
	if (!temp)
		return (0);
	base = "0123456789abcdef";
	if (nb == 0)
		return (write(1, "0", 1), free(temp), 1);
	while (i >= 0)
	{
		temp[i] = base[nb % 16];
		nb /= 16;
		i--;
	}
	write(1, "0x", 2);
	write(1, temp, ft_hexlen(result));
	free(temp);
	return (2 + ft_hexlen(result));
}
