/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:30:31 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/24 10:38:27 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_printf(const char *str, ...)
{
	int		return_value;
	int		whitespaces;
	int		i;
	va_list	arglist;

	whitespaces = 0;
	return_value = 0;
	va_start(arglist, str);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			return_value += ft_printer((str + i), arglist);
			whitespaces += 2;
			i += 2;
		}
		else if (str[i])
			ft_putchar_fd(str[i++], 1);
	}
	va_end(arglist);
	return (return_value + (int)i - whitespaces);
}
