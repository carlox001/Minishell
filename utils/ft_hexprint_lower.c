/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexprint_lower.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:00:05 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/24 10:37:14 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	ft_hexlen(unsigned int nb)
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

int	ft_hexprint_lower(unsigned int nb)
{
	char			*base;
	char			*temp;
	int				i;
	unsigned int	result;

	result = nb;
	i = ft_hexlen(nb) - 1;
	temp = (char *)ft_calloc((i + 2), sizeof(char));
	if (!temp)
		return (0);
	base = "0123456789abcdef";
	if (nb == 0)
	{
		write(1, "0", 1);
		return (free(temp), 1);
	}
	while (i >= 0)
	{
		temp[i--] = base[nb % 16];
		nb /= 16;
	}
	ft_putstr_fd(temp, 1);
	free(temp);
	return (ft_hexlen(result));
}
