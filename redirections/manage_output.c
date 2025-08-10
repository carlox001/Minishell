/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:30:36 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/17 14:17:22 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_output(t_program *shell, int k, int i, char ***mtx_hub)
{
	char	**tmp;

	if (k == -1)
		return (1);
	if (k > 0)
	{
		tmp = realloc_without_redir(mtx_hub[i], k, '>');
		if (tmp[0] == NULL)
		{
			close_in_out(shell->out, k - 1, 1);
			close_in_out(shell->fd, 2, 0);
			free_matrix(tmp);
			return (1);
		}
		free_matrix(mtx_hub[i]);
		mtx_hub[i] = matrix_dup(tmp);
		free_matrix(tmp);
	}
	if (mtx_hub[i][0] == NULL)
		return (1);
	return (0);
}

int	open_files_out(char **mtx, t_program *shell)
{
	int	i;
	int	j;

	i = counter_in_out('>', mtx);
	if (i == 0)
		return (0);
	shell->out = (int *)malloc(sizeof(int) * i);
	if (shell->out == NULL)
		return (-1);
	initialize_files_in(&i, &j, NULL, 0);
	while (mtx[i])
	{
		if (mtx[i][0] == '>' && mtx[i][1] == '>')
		{
			if (double_redirection(&i, &j, mtx, shell) == -1)
				return (-1);
		}
		else if (mtx[i][0] == '>')
		{
			if (single_redirection(&i, &j, mtx, shell) == -1)
				return (-1);
		}
		i++;
	}
	return (j);
}

int	single_redirection(int *i, int *j, char **mtx, t_program *shell)
{
	char	*tmp;

	(*i)++;
	tmp = remove_couple_quotes(mtx[*i]);
	shell->out[*j] = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (shell->out[*j] == -1)
	{
		ft_putstr_fd("shell: ", 2);
		ft_putstr_fd(tmp, 2);
		ft_putstr_fd(": error\n", 2);
		shell->exit_code = 1;
		free(shell->out);
		free(tmp);
		return (-1);
	}
	(*j)++;
	free(tmp);
	return (0);
}

int	double_redirection(int *i, int *j, char **mtx, t_program *shell)
{
	(*i)++;
	shell->out[*j] = open(mtx[*i], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (shell->out[*j] == -1)
	{
		ft_putstr_fd("shell: ", 2);
		ft_putstr_fd(mtx[*i], 2);
		ft_putstr_fd(": error\n", 2);
		shell->exit_code = 1;
		free(shell->out);
		return (-1);
	}
	(*j)++;
	return (0);
}
