/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:32:04 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/24 12:49:56 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*getpath(char **envp)
{
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			path = envp[i];
			break ;
		}
		i++;
	}
	return (path);
}

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0 && ft_strlen(cmd) == 4)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 3) == 0 && ft_strlen(cmd) == 3)
		return (1);
	else if (ft_strncmp(cmd, "env", 3) == 0 && ft_strlen(cmd) == 3)
		return (1);
	else if (ft_strncmp(cmd, "cd", 2) == 0 && ft_strlen(cmd) == 2)
		return (1);
	else if (ft_strncmp(cmd, "export", 6) == 0 && ft_strlen(cmd) == 6)
		return (1);
	else if (ft_strncmp(cmd, "unset", 5) == 0 && ft_strlen(cmd) == 5)
		return (1);
	else if (ft_strncmp(cmd, "exit", 4) == 0 && ft_strlen(cmd) == 4)
		return (1);
	return (0);
}

char	*path_find(char **envp, char *command)
{
	int		i;
	int		flag;
	char	*path;
	char	**paths;
	char	*path_joined;

	if (command[0] == '/')
		return (command);
	i = 0;
	flag = 0;
	path = getpath(envp);
	if (path == NULL)
		return (NULL);
	paths = ft_split(&path[5], ':');
	while (paths[i])
	{
		path_joined = ft_strjoin(paths[i], "/");
		if (is_builtin(command) == 1)
			flag = 1;
		path = ft_strjoin(path_joined, command);
		if (if_access(path, flag) == 1)
			return (free(path_joined), free_matrix(paths), path);
		path_clear(path, path_joined, &i);
	}
	return (free_matrix(paths), NULL);
}

void	path_clear(char *path, char *path_joined, int *i)
{
	free(path);
	free(path_joined);
	(*i)++;
}

char	**get_full_cmd(t_program *shell)
{
	int		len;
	int		i;
	char	**full_cmd;

	len = 0;
	shell->i = 0;
	while (shell->mtx_line[shell->i + len])
	{
		if (shell->mtx_line[shell->i + len][0] != '<' && \
			shell->mtx_line[shell->i + len][0] != '>' && \
			shell->mtx_line[shell->i + len][0] != '|')
			len++;
		else
			break ;
	}
	shell->i += len;
	full_cmd = (char **)malloc(sizeof(char *) * (len + 1));
	if (full_cmd == NULL)
		return (NULL);
	i = -1;
	while (++i < len)
		full_cmd[i] = remove_couple_quotes(shell->mtx_line[i]);
	full_cmd[i] = NULL;
	return (full_cmd);
}
