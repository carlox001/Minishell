/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_hub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:32:04 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/24 13:15:12 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_commands(char *cmd, t_program *shell, int k, char ***mtx_hub)
{
	int		check;

	if (k != -1)
		close_in_out(shell->out, k, 1);
	check = check_builtin(cmd, shell, mtx_hub);
	if (check == 1)
	{
		shell->flag_builtin = 1;
		free_matrix(shell->mtx_line);
		return (1);
	}
	else if (exec_non_builtin(shell, 0, mtx_hub) == 1)
		return (1);
	return (0);
}

int	check_builtin(char *cmd, t_program *shell, char ***mtx_hub)
{
	char	*tmp;

	tmp = remove_couple_quotes(cmd);
	if (ft_strncmp(tmp, "echo", 4) == 0 && ft_strlen(tmp) == 4)
		return (free(tmp), ft_echo(shell), 1);
	else if (ft_strncmp(tmp, "pwd", 3) == 0 && ft_strlen(tmp) == 3)
		return (free(tmp), ft_pwd(shell), 1);
	else if (ft_strncmp(tmp, "env", 3) == 0 && ft_strlen(tmp) == 3)
		return (free(tmp), ft_env(shell), 1);
	else if (ft_strncmp(tmp, "cd", 2) == 0 && ft_strlen(tmp) == 2)
		return (free(tmp), ft_cd(shell), 1);
	else if (ft_strncmp(tmp, "export", 6) == 0 && ft_strlen(tmp) == 6)
		return (free(tmp), ft_export(shell), 1);
	else if (ft_strncmp(tmp, "unset", 5) == 0 && ft_strlen(tmp) == 5)
		return (free(tmp), ft_unset(shell), 1);
	else if (ft_strncmp(tmp, "exit", 4) == 0 && ft_strlen(tmp) == 4)
		return (free(tmp), ft_exit(shell, mtx_hub), 1);
	return (free(tmp), 0);
}

int	exec_non_builtin(t_program *shell, int index, char ***mtx_hub)
{
	char	**full_cmd;

	shell->path = NULL;
	shell->path = path_find(shell->env, shell->mtx_line[index]);
	if (shell->path == NULL && shell->mtx_line[0][0] != '.')
	{
		shell->i = matrix_len(shell->mtx_line);
		return (free(shell->path), free_all(shell, 0), 1);
	}
	full_cmd = get_full_cmd(shell);
	if (shell->path == NULL)
	{
		free(shell->path);
		shell->path = ft_strdup(shell->mtx_line[0]);
	}
	if (execve(shell->path, full_cmd, shell->env) == -1)
	{
		if (shell->path)
			free(shell->path);
		else
			shell->path = NULL;
		shell->flag_cmd_not_found = 1;
		failed_execve(full_cmd, shell, mtx_hub);
	}
	return (0);
}

void	failed_execve(char **full_cmd, t_program *shell, char ***mtx_hub)
{
	int	fd;

	fd = open(full_cmd[0], __O_DIRECTORY);
	if (fd > 0)
	{
		printf("shell: %s: is a directory\n", full_cmd[0]);
		clear_non_builtin(shell, mtx_hub, &full_cmd);
		close(fd);
		correct_exit(126);
	}
	else
	{
		ft_putstr_fd("shell: ", 2);
		ft_putstr_fd("no such file or directory\n", 2);
		clear_non_builtin(shell, mtx_hub, &full_cmd);
		correct_exit(127);
	}
}

void	clear_non_builtin(t_program *shell, char ***mtx_hub, \
char ***full_cmd)
{
	if (*full_cmd[0][0] == '.')
		free_matrix(shell->mtx_line);
	else
		free(shell->mtx_line);
	free_all(shell, 1);
	free_matrix_pointer(mtx_hub);
	free_matrix(*full_cmd);
}
