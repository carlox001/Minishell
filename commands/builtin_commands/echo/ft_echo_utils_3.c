/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cazerini <cazerini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:45:59 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/21 18:29:13 by cazerini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	update_counter_and_i(int *i, int *counter)
{
	(*i)++;
	(*counter)--;
}

int	only_quotes(char *str, int *flag)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
			return (1);
		if (str[i] == '\'')
		{
			i++;
			*flag = 0;
			if (str[i] != '\'')
				return (1);
		}
		if (str[i] == '\"')
		{
			i++;
			*flag = 1;
			if (str[i] != '\"')
				return (1);
		}
		i++;
	}
	return (0);
}

void	alloc_only_quote(char **sub_str, int flag)
{
	char	*tmp;

	tmp = *sub_str;
	if (flag == 0)
		*sub_str = ft_strdup("\'\'");
	else
		*sub_str = ft_strdup("\"\"");
	free(tmp);
}

void	echo_if(t_program *shell, char **str2, int *i, int len)
{
	char	*tmp;

	tmp = *str2;
	*str2 = remove_couple_quotes(*str2);
	free(tmp);
	ft_echo_core(shell, *str2, i, len);
}
