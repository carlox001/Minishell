/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:53:39 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/25 13:20:48 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ambiguous_redirect(t_program *shell)
{
	if (shell->mtx_line[matrix_len(shell->mtx_line) - 1][0] == '<' || \
		shell->mtx_line[matrix_len(shell->mtx_line) - 1][0] == '>')
	{
		ft_putstr_fd("shell: ", 2);
		ft_putstr_fd(shell->mtx_line[matrix_len(shell->mtx_line) - 1], 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		shell->exit_code = 1;
		free_matrix(shell->mtx_line);
		return (0);
	}
	return (1);
}

void	update_exit_status(t_program *shell)
{
	shell->exit_code /= 256;
	shell->status = (unsigned char *)ft_itoa(shell->exit_code);
	shell->exit_code = ft_atoi((const char *)shell->status);
	free(shell->status);
}

void	waiting(t_program *shell)
{
	if (shell->num_cmd != 1)
	{
		waitpid(shell->id_to_wait, &shell->exit_code, 0);
		while (wait(NULL) > 0)
			;
		update_exit_status(shell);
	}
	else
	{
		while (wait(&shell->exit_code) > 0)
			update_exit_status(shell);
	}
}

void	else_father(t_program *shell, int *i, int *j, char ***mtx_hub)
{
	if (*i + 1 == shell->num_cmd && shell->num_cmd > 1)
	{
		shell->id_to_wait = shell->fork_id;
		if (!(ft_strncmp("sleep", mtx_hub[*i][0], 5) == 0 && \
	ft_strlen(mtx_hub[*i][0]) == 5) && \
	!(ft_strncmp("cat", mtx_hub[*i][0], 3) == 0 && \
	ft_strlen(mtx_hub[*i][0]) == 3))
			shell->check_pipe_ex_co = 1;
		if (ft_strncmp("grep", mtx_hub[*i][0], 4) == 0 && \
		ft_strlen(mtx_hub[*i][0]) == 4)
		{
			if (matrix_len(mtx_hub[*i]) == 2)
				shell->check_pipe_ex_co = 0;
			else
				shell->check_pipe_ex_co = 1;
		}
	}
	father(shell, *j);
}

int	exec_more_commands(t_program *shell, int j, int i, char ***mtx_hub)
{
	signal(SIGINT, sig_handler_child);
	signal(SIGQUIT, sig_handler_child);
	while (i < shell->num_cmd)
	{
		if (pipe(shell->fd) == -1)
		{
			close(shell->input);
			close(shell->output);
			return (1);
		}
		shell->fork_id = fork();
		if (shell->fork_id == -1)
			return (1);
		else if (shell->fork_id == 0 && child(shell, i, j, mtx_hub) == 1)
			failed_child(shell, mtx_hub);
		else
			else_father(shell, &i, &j, mtx_hub);
		update_counter_exec(&j, &i);
	}
	return (0);
}
