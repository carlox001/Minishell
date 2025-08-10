/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 09:36:05 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/24 10:39:58 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_putchar_count_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_putstr_count_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
	return (i);
}

int	ft_numlen(int nb)
{
	int	len;

	len = 0;
	if (nb == 0)
	{
		return (1);
	}
	if (nb < 0)
	{
		len++;
	}
	while (nb != 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

int	ft_unsigned_numlen(unsigned int nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}
