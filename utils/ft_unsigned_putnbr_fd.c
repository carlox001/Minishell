/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_putnbr_fd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:52:46 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/24 10:39:50 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_unsigned_putnbr_fd(unsigned int n, int fd)
{
	char	nb[11];
	int		i;
	int		numb;

	i = 0;
	numb = n;
	if (n == 0)
		write(fd, "0", 1);
	while (n > 0)
	{
		nb[i++] = (n % 10) + '0';
		n /= 10;
	}
	while (--i >= 0)
		write(fd, &nb[i], 1);
	return (ft_unsigned_numlen(numb));
}
