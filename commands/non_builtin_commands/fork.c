/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:48:35 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/24 13:27:52 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// il figlio che esegue i comandi dell'execve
int	child(t_program *shell, int i, int pipe_cmd, char ***mtx_hub)
{
	char	*path;
	int		flag;

	shell->flag_cmd_not_found = 0;
	flag = 0;
	if (open_files_in_child(shell, i, mtx_hub) == -1)
	{
		close(shell->input);
		close(shell->output);
		return (1);
	}
	shell->mtx_line = matrix_dup(mtx_hub[i]);
	path = NULL;
	redirect_in_out_child(shell, pipe_cmd, path);
	if (is_builtin(shell->mtx_line[0]) == 1)
		flag = 1;
	if (check_commands(shell->mtx_line[0], shell, shell->num_fd, mtx_hub) == 1)
		close_child(flag, shell, &mtx_hub);
	return (0);
}

// apre i file in input e output e imposta 
//come flussi gli ultimi file aperti
int	open_files_in_child(t_program *shell, int i, char ***mtx_hub)
{
	shell->num_fd = open_files_in(mtx_hub[i], shell);
	if (shell->num_fd == -1)
		return (-1);
	if (redir_input(shell, i, mtx_hub, 0) == 1)
	{
		close(shell->input);
		close(shell->output);
		free_all(shell, 1);
		free_matrix_pointer(mtx_hub);
		correct_exit(1);
	}
	shell->num_fd = open_files_out(mtx_hub[i], shell);
	if (shell->num_fd == -1)
		return (-1);
	if (redir_output(shell, shell->num_fd, i, mtx_hub) == 1)
	{
		free_all(shell, 1);
		free_matrix_pointer(mtx_hub);
		close(shell->input);
		close(shell->output);
		correct_exit(1);
	}
	shell->num_fd--;
	return (0);
}

// redirige l'input e l'output dei comandi del programma
void	redirect_in_out_child(t_program *shell, int pipe_cmd, char *path)
{
	if (pipe_cmd > 0)
		if_redirect(shell, &path);
	else
	{
		shell->tmp = remove_couple_quotes(shell->mtx_line[0]);
		path = path_find(shell->env, shell->tmp);
		if (path == NULL && is_builtin(shell->tmp) == 0 && \
		shell->tmp[0] != '.')
			print_error_cringe(shell->tmp);
		else if (shell->num_fd >= 0)
			dup2(shell->out[shell->num_fd], STDOUT_FILENO);
		else
			dup2(shell->output, STDOUT_FILENO);
		if (path && shell->tmp[0] == '.')
			free(path);
		close_all_files(shell->fd, shell->output, shell->input);
		free(shell->tmp);
	}
}

void	father(t_program *shell, int j)
{
	if (j > 0)
		close_fds(shell->fd, 1, shell->input);
	else if (j == 0)
		close_fds(shell->fd, 0, shell->input);
}

void	failed_child(t_program *shell, char ***mtx_hub)
{
	close(shell->fd[0]);
	close(shell->fd[1]);
	close(shell->input);
	close(shell->output);
	free_matrix_pointer(mtx_hub);
	free_all(shell, 1);
	correct_exit(1);
}
