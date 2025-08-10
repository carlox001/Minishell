/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:22:24 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/14 15:47:27 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// alloca la matrice della riga che ci passano
int	matrix_handler(char *str, t_program *shell)
{
	if (alloc_mtx_line(shell, str) == 1)
		return (1);
	shell->i = 0;
	shell->j = 0;
	shell->i_p = 0;
	while (shell->i < shell->len)
	{
		if (matrix_handler_core(str, shell, &(shell->i), &(shell->j)) == 1)
			return (1);
		if (str[shell->i] == '|' || \
			str[shell->i] == '>' || str[shell->i] == '<')
		{
			if (operators_allocation(str, shell, shell->i, shell->j) == 1)
				return (1);
			operators_core(str, shell, &(shell->i), &(shell->j));
			shell->j++;
		}
		else if (shell->i < shell->len)
			shell->i++;
		shell->i_p = shell->i;
	}
	shell->mtx_line[shell->words] = NULL;
	return (0);
}

int	alloc_mtx_line(t_program *shell, char *str)
{
	shell->words = count_words(str, shell) + 1;
	if (shell->words == 0)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command not found\n", 2);
		shell->exit_code = 127;
		return (1);
	}
	shell->mtx_line = (char **)ft_calloc(sizeof(char *), (shell->words + 1));
	if (shell->mtx_line == NULL)
		return (1);
	return (0);
}

int	matrix_handler_core_quotes(t_program *shell, char *str, int *i)
{
	int	flag;

	flag = 0;
	if ((str[*i] == '\'' || str[*i] == '\"'))
	{
		while (flag == 0)
		{
			if (quotes_core(str, shell, &(shell->i_p), &flag) == 1)
				return (1);
			if (str[*i] == '\0' || str[*i] == ' ' || \
				str[*i] == '|' || str[*i] == '<' || \
				str[*i] == '>')
				flag = 1;
		}
		shell->mtx_line[shell->j] = \
			ft_substr(str, shell->i_p, (shell->i - shell->i_p));
		if (shell->mtx_line[shell->j] == NULL)
			return (1);
		shell->j++;
		shell->i_p = shell->i;
	}
	return (0);
}

int	matrix_handler_core(char *str, t_program *shell, int *i, int *j)
{
	while (str[*i] == ' ' && str[*i])
	{
		(*i)++;
		shell->i_p++;
	}
	if (*i > 0 && (str[*i - 1] == '\"' || str[*i - 1] == '\''))
		(*i)++;
	while (isvalid(str, *i) == 1)
		(*i)++;
	if (((*i - shell->i_p) != 0) && (str[*i] != '"' && str[*i] != '\''))
	{
		shell->mtx_line[*j] = ft_substr(str, shell->i_p, (*i - shell->i_p));
		if (shell->mtx_line[*j] == NULL)
			return (1);
		(*j)++;
	}
	if (matrix_handler_core_quotes(shell, str, i) == 1)
		return (1);
	return (0);
}
