/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 10:48:43 by cazerini          #+#    #+#             */
/*   Updated: 2025/05/04 13:30:04 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	cd_absolute_path(char *str, t_program *shell)
{
	char	*path;

	if (str[0] == '/')
	{
		path = ft_strdup(str);
		if (chdir(str) == -1)
		{
			print_cd_error(str);
			shell->exit_code = 1;
			free(path);
		}
		else
		{
			shell->exit_code = 0;
			refresh_directory(path, shell, 0);
		}
		return (1);
	}
	return (0);
}

int	cd_relative_path(char *str, t_program *shell)
{
	int		i;
	char	*save_old_path;

	save_old_path = ft_strdup(shell->pwd);
	i = 0;
	if (count_backs(str, shell) == -1)
		return (-1);
	while (str[i])
	{
		if (relative_path_core(str, &i, shell, save_old_path) == -1)
			return (-1);
		if (str[i] != '\0')
			i++;
	}
	free(shell->old_pwd);
	shell->old_pwd = ft_strdup(save_old_path);
	free(save_old_path);
	env_refresh_dir(shell);
	return (0);
}

int	relative_path_core(char *str, int *i, t_program *shell, char *sv)
{
	char	*path;
	int		j;

	if (str[(*i)] == '.' && str[(*i) + 1] == '.')
	{
		if (str[(*i) + 2] == '/' || str[(*i) + 2] == '\0')
		{
			(*i) += 2;
			if (str[(*i)] == '\0')
				(*i)--;
			path = cd_back(shell);
			if (path != NULL)
				refresh_directory(path, shell, 1);
		}
	}
	if (str[(*i)] != '/')
	{
		j = (*i);
		while (str[(*i)] != '/' && str[(*i)])
			(*i)++;
		if (relative_back_slash(str, shell, (*i), j) == -1)
			return (chdir(sv), free(sv), -1);
	}
	return (0);
}

int	relative_back_slash(char *str, t_program *shell, int i, int j)
{
	char	*path;
	char	*tmp;

	path = ft_substr(str, j, i - j);
	if (!(ft_strncmp(shell->pwd, "/", 1) == 0 && \
		ft_strlen(shell->pwd) == 1))
	{
		tmp = path;
		path = ft_strjoin("/", path);
		free(tmp);
	}
	tmp = path;
	path = ft_strjoin(shell->pwd, path);
	free(tmp);
	if (chdir(path) == -1)
		return (free(path), -1);
	else
		end_relative_cd(shell, path);
	return (0);
}

void	end_relative_cd(t_program *shell, char *path)
{
	char	*tmp;

	if (path[ft_strlen(path) - 1] == '/')
	{
		tmp = path;
		path = ft_substr(path, 0, ft_strlen(path) - 1);
		free(tmp);
	}
	refresh_directory(path, shell, 1);
}
