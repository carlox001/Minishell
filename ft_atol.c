/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:02:43 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/24 11:16:29 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_atol(char *ptr)
{
	int			sign;
	long long	res;

	sign = 1;
	res = 0;
	while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n' || \
	*ptr == '\v' || *ptr == '\f' || *ptr == '\r')
		ptr++;
	if (*ptr == '+' || *ptr == '-')
	{
		if (*ptr == '-')
			sign = -1;
		ptr++;
	}
	while (*ptr >= 48 && *ptr <= 57)
	{
		res = res * 10 + (*ptr - '0');
		ptr++;
	}
	return (res * sign);
}
