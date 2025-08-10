/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:48:35 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/24 13:27:15 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_error_cringe(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	close_child(int flag, t_program *shell, char ****mtx_hub)
{
	free_matrix_pointer(*mtx_hub);
	if (flag == 1)
		free_all(shell, 1);
	close(shell->input);
	close(shell->output);
	if (shell->num_cmd != 1 && flag == 1)
		correct_exit(shell->exit_code);
	correct_exit(127);
}

void	correct_exit(int code)
{
	close(1);
	close(0);
	exit(code);
}

void	if_redirect(t_program *shell, char **path)
{
	shell->tmp = remove_couple_quotes(shell->mtx_line[0]);
	*path = path_find(shell->env, shell->tmp);
	if (*path == NULL && is_builtin(shell->tmp) == 0 && \
	shell->tmp[0] != '.')
		print_error_cringe(shell->tmp);
	else if (shell->num_fd >= 0)
		dup2(shell->out[shell->num_fd], STDOUT_FILENO);
	else
		dup2(shell->fd[1], STDOUT_FILENO);
	if (*path && shell->tmp[0] == '.')
		free(*path);
	close_all_files(shell->fd, shell->output, shell->input);
	free(shell->tmp);
}
