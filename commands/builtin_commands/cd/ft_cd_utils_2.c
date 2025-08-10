/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 10:55:57 by cazerini          #+#    #+#             */
/*   Updated: 2025/05/04 13:23:35 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	cd_no_char(char *str, t_program *shell)
{
	int		counter;
	char	*path;

	counter = count_backs(str, shell);
	if (counter == -1)
		return ;
	if (str[0] == '/')
	{
		cd_root(shell);
		return ;
	}
	while (counter > 0)
	{
		path = cd_back(shell);
		if (path == NULL)
			return ;
		refresh_directory(path, shell, 0);
		counter--;
	}
}

int	no_char(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '.' && str[i] != '/')
			return (1);
		i++;
	}
	return (0);
}

void	only_cd(t_program *shell)
{
	if (shell->home_path == NULL)
	{
		ft_putstr_fd("shell: cd: HOME not set\n", 2);
		return ;
	}
	else
	{
		free(shell->old_pwd);
		shell->old_pwd = ft_strdup(shell->pwd);
		free(shell->pwd);
		shell->pwd = ft_strdup(shell->home_path);
		free(shell->curr_dir);
		shell->curr_dir = ft_strdup("");
		if (chdir(shell->home_path) == -1)
			return ;
		env_refresh_dir(shell);
	}
}

void	cd_root(t_program *shell)
{
	free(shell->old_pwd);
	shell->old_pwd = ft_strdup(shell->pwd);
	free(shell->pwd);
	shell->pwd = ft_strdup("/");
	free(shell->curr_dir);
	shell->curr_dir = ft_strdup("/");
	if (chdir(shell->pwd) == -1)
		return ;
	env_refresh_dir(shell);
}

char	*cd_back(t_program *shell)
{
	char	*path;
	int		i;

	if (shell->pwd[0] == '/' && shell->pwd[1] == '\0')
		return (NULL);
	i = ft_strlen(shell->pwd) - 1;
	while (shell->pwd[i])
	{
		if (shell->pwd[i] == '/')
			break ;
		i--;
	}
	if (i == 0)
		i++;
	path = ft_substr(shell->pwd, 0, i);
	if (chdir(path) == -1)
		return (free(path), NULL);
	return (path);
}
