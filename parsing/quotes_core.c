/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cazerini <cazerini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:04:58 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/21 15:56:20 by cazerini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quotes_core(char *str, t_program *shell, int *i_p, int *flag)
{
	shell->i_p = (*i_p);
	if (double_quote(str, shell, flag) == 1)
		return (1);
	else if (single_quote(str, shell, flag) == 1)
		return (1);
	return (0);
}

int	double_quote(char *str, t_program *shell, int *flag)
{
	if (str[shell->i] == '\"')
	{
		shell->i++;
		while (str[shell->i] && str[shell->i] != '\"')
			shell->i++;
		if (str[shell->i] != '\0')
			shell->i++;
		if ((str[shell->i] == ' ' || str[shell->i] == '\0'))
			*flag = 1;
		else
		{
			while (str[shell->i] && isvalid(str, shell->i) == 1 && \
			str[shell->i] != ' ')
				shell->i++;
		}
	}
	return (0);
}

//separa in funzioni e bella
int	single_quote(char *str, t_program *shell, int *flag)
{
	if (str[shell->i] == '\'')
	{
		shell->i++;
		while (str[shell->i] && str[shell->i] != '\'')
			shell->i++;
		if (str[shell->i] != '\0')
			shell->i++;
		if (str[shell->i] == ' ' || str[shell->i] == '\0')
			*flag = 1;
		else
		{
			while (str[shell->i] && isvalid(str, shell->i))
				shell->i++;
		}
	}
	return (0);
}
