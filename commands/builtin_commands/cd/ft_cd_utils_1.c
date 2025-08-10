/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 10:55:57 by cazerini          #+#    #+#             */
/*   Updated: 2025/05/04 13:25:17 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	env_refresh_dir(t_program *shell)
{
	int		i;
	char	*tmp;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "PWD", 3) == 0)
		{
			free(shell->env[i]);
			tmp = ft_strdup(shell->pwd);
			shell->env[i] = ft_strjoin("PWD=", tmp);
			free(tmp);
		}
		if (ft_strncmp(shell->env[i], "OLDPWD", 6) == 0)
		{
			free(shell->env[i]);
			tmp = ft_strdup(shell->old_pwd);
			shell->env[i] = ft_strjoin("OLDPWD=", tmp);
			free(tmp);
		}
		i++;
	}
}

void	refresh_directory(char *path, t_program *shell, int flag)
{
	char	*tmp;

	if (flag != 1)
	{
		free(shell->old_pwd);
		shell->old_pwd = ft_strdup(shell->pwd);
	}
	free(shell->pwd);
	shell->pwd = ft_strdup(path);
	tmp = shell->curr_dir;
	shell->curr_dir = ft_substr(shell->pwd, ft_strlen(shell->home_path), \
	(ft_strlen(shell->pwd) - ft_strlen(shell->home_path)));
	free(tmp);
	free(path);
	if (flag != 1)
		env_refresh_dir(shell);
}

char	*format_str(char *old_str)
{
	char	*new_str;
	char	*tmp;
	int		i;
	int		counter;

	i = ft_strlen(old_str);
	counter = 0;
	while (old_str[i])
	{
		if (old_str[i] != '.' && old_str[i] != '/')
			break ;
		i--;
	}
	i++;
	while (old_str[i] && old_str[i] == '.')
		counter++;
	new_str = ft_strtrim(old_str, "./");
	while (counter > 0)
	{
		tmp = new_str;
		new_str = ft_strjoin(new_str, ".");
		free(tmp);
		counter--;
	}
	return (new_str);
}

int	only_backslash(char *str)
{
	int	i;

	i = 2;
	while (str[i])
	{
		if (str[i] != '/')
			return (1);
		i++;
	}
	return (0);
}

int	count_backs(char *str, t_program *shell)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == '.' && str[i + 1] == '.' && str[i + 1] != '\0')
		{
			i += 2;
			counter++;
			if (str[i] == '.' && str[i] != '\0')
			{
				print_cd_error(str);
				shell->exit_code = 1;
				return (-1);
			}
			if (str[i] == '\0')
				i--;
		}
		i++;
	}
	return (counter);
}
