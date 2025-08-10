/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_retputnbr_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 14:38:31 by sfiorini          #+#    #+#             */
/*   Updated: 2025/02/03 17:05:21 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_intcheck(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return (11);
	}
	return (ft_retputnbr_fd(n, fd));
}

int	ft_retputnbr_fd(int n, int fd)
{
	char	nb[11];
	int		i;
	int		numb;

	numb = n;
	i = 0;
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n == 0)
		write(fd, "0", 1);
	while (n > 0)
	{
		nb[i++] = (n % 10) + '0';
		n /= 10;
	}
	while (--i >= 0)
		write(fd, &nb[i], 1);
	return (ft_numlen(numb));
}
