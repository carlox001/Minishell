/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 22:13:11 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/25 13:49:32 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	flag_cmds(t_program *shell, int *flag, int i, char **tmp)
{
	if (tmp[i] != NULL && check_flag_builtin(tmp, i) == 1)
		shell->flag_builtin++;
	*flag = 1;
}

void	skip_quote_cmd(char **tmp, int *i)
{
	if (tmp[*i] && tmp[*i][0] == '\"')
	{
		if (tmp[*i] != NULL)
			(*i)++;
	}
	if (tmp[*i] && tmp[*i][0] == '\'')
	{
		if (tmp[*i] != NULL)
			(*i)++;
	}
}

void	not_null_cmd_count(char **tmp, int *i)
{
	if (tmp[*i] != NULL)
	{
		while ((tmp[*i][0] == '<' || tmp[*i][0] == '>'))
			*i += 2;
	}
}

int	count_commands(t_program *shell)
{
	int		i;
	int		count;
	char	**tmp;
	int		flag;

	flag = 0;
	i = 0;
	count = 1;
	shell->flag_builtin = 0;
	tmp = matrix_dup(shell->mtx_line);
	while (tmp[i])
	{
		skip_quote_cmd(tmp, &i);
		not_null_cmd_count(tmp, &i);
		if (tmp[i] != NULL && tmp[i][0] == '|')
			count++;
		if (flag == 0)
			flag_cmds(shell, &flag, i, tmp);
		if (tmp[i] != NULL)
			i++;
	}
	free_matrix(tmp);
	return (count);
}
