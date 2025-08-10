/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:53:39 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/25 12:04:12 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec(t_program *shell)
{
	int		j;
	int		check;
	char	***mtx_hub;

	mtx_hub = NULL;
	if (ambiguous_redirect(shell) == 0)
		return (0);
	j = set_exec(shell, &mtx_hub);
	check = exec_core(shell, j, shell->num_cmd, mtx_hub);
	close(shell->input);
	close(shell->output);
	if (check == 1)
		return (1);
	if (check == -1)
		return (free_matrix_pointer(mtx_hub), -1);
	waiting(shell);
	close_here_doc(shell);
	set_exec_signals();
	free_matrix_pointer(mtx_hub);
	return (0);
}

int	set_exec(t_program *shell, char ****mtx_hub)
{
	int		j;

	shell->output = dup(STDOUT_FILENO);
	shell->input = dup(STDIN_FILENO);
	shell->num_cmd = count_commands(shell);
	count_commands2(shell);
	*mtx_hub = alloc_mtx(shell->num_cmd, shell);
	free_matrix(shell->mtx_line);
	j = shell->num_cmd - 1;
	shell->i = 0;
	return (j);
}

int	exec_core(t_program *shell, int j, int num_cmd, char ***mtx_hub)
{
	int		i;
	int		check;

	i = 0;
	check = 0;
	if (num_cmd == 1 && shell->flag_builtin >= 1)
	{
		check = exec_one_command(shell, i, mtx_hub);
		if (check == 1)
			return (2);
		if (check == -1)
			return (-1);
	}
	else
	{
		check = exec_more_commands(shell, j, i, mtx_hub);
		if (check == 1)
			return (1);
		if (check == -1)
			return (-1);
	}
	close(shell->input);
	close(shell->output);
	return (0);
}

void	closes_in_cmd(t_program *shell, int k)
{
	if (k - 1 >= 0)
		close_in_out(shell->out, k - 1, 1);
	dup2(shell->output, STDOUT_FILENO);
	close(shell->output);
}

int	exec_one_command(t_program *shell, int i, char ***mtx_hub)
{
	int		k;

	shell->num_fd = open_files_in(mtx_hub[i], shell);
	if (shell->num_fd == -1)
		return (-1);
	if (redir_input(shell, i, mtx_hub, 1) == 1)
		return (1);
	k = open_files_out(mtx_hub[i], shell);
	if (k == -1)
		return (-1);
	if (redir_output(shell, k, i, mtx_hub) == 1)
		return (1);
	if (k - 1 >= 0)
		dup2(shell->out[k - 1], STDOUT_FILENO);
	shell->mtx_line = matrix_dup(mtx_hub[i]);
	if (check_commands(shell->mtx_line[0], shell, -1, mtx_hub) == 1)
		return (closes_in_cmd(shell, k), 1);
	return (closes_in_cmd(shell, k), 0);
}
