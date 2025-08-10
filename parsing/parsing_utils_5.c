/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:04:25 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/25 12:17:48 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_flag(int *flag_s, int *flag_d, char c)
{
	if (c == '\"')
	{
		if (*flag_d == 0)
			*flag_d = 1;
		else
			*flag_d = 0;
	}
	if (c == '\'' && *flag_d == 0)
	{
		if (*flag_s == 0)
			*flag_s = 1;
		else
			*flag_s = 0;
	}
}

int	check_pipe(char **mtx)
{
	int	i;

	i = 0;
	while (mtx[i])
	{
		if (mtx[i][0] == '|' && mtx[i + 1][0] == '|')
			return (1);
		if (mtx[i] != NULL)
			i++;
	}
	return (0);
}

void	if_dollar(t_program *shell, int *k)
{
	char	*tmp;

	shell->expansion_flag = 1;
	tmp = shell->mtx_line[*k];
	shell->mtx_line[*k] = expansion_variable2(tmp, shell);
	free(tmp);
}

void	add_quote(char **new_str)
{
	char	*tmp;

	if (*new_str[0] == '\"')
	{
		tmp = *new_str;
		*new_str = ft_strjoin(*new_str, "\"");
		free(tmp);
	}
	else if (*new_str[0] == '\'')
	{
		tmp = *new_str;
		*new_str = ft_strjoin(*new_str, "\'");
		free(tmp);
	}
}

void	quotes_skips(char *str, int *i)
{
	if (str[*i] == '\"')
	{
		(*i)++;
		while (str[*i] && str[*i] != '\"')
			(*i)++;
	}
	if (str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] && str[*i] != '\'')
			(*i)++;
	}
}
