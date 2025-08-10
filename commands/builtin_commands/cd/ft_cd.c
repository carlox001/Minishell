/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:30:14 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/09 18:52:28 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	ft_cd(t_program *shell)
{
	if (shell->mtx_line[shell->i + 1] == NULL)
		only_cd(shell);
	else if (shell->mtx_line[shell->i + 2] != NULL)
		return (print_too_many_arg(shell));
	else if (cd_checks(shell) == 1)
		return ;
	else if (ft_strlen(shell->mtx_line[shell->i + 1]) >= 4096)
	{
		shell->exit_code = 1;
		return (ft_putstr_fd("shell: cd: too much longer\n", 2));
	}
	else if (cd_absolute_path(shell->mtx_line[shell->i + 1], shell) == 1)
	{
		shell->exit_code = 1;
		return ;
	}
	else if (cd_relative_path(shell->mtx_line[shell->i + 1], shell) == -1)
	{
		relative_error(shell);
		return ;
	}
	shell->exit_code = 0;
	shell->i = matrix_len(shell->mtx_line);
	return ;
}

void	cd_oldpwd(t_program *shell)
{
	char	**tmp;
	char	*path;

	tmp = malloc(sizeof(char *) * 1);
	tmp[0] = ft_strdup("OLDPWD");
	path = ft_getenv(shell, tmp);
	if (path == NULL)
	{
		ft_putstr_fd("shell: cd: OLDPWD not set\n", 2);
		free(tmp[0]);
		free(tmp);
		return ;
	}
	free(tmp[0]);
	free(tmp);
	if (chdir(path) == -1)
		return (free(path));
	refresh_directory(path, shell, 0);
}

int	cd_checks(t_program *shell)
{
	if (shell->mtx_line[shell->i + 1][0] == '-')
	{
		cd_oldpwd(shell);
		return (1);
	}
	else if (no_char(shell->mtx_line[shell->i + 1]) == 0)
	{
		cd_no_char(shell->mtx_line[shell->i + 1], shell);
		shell->i = matrix_len(shell->mtx_line);
		shell->exit_code = 0;
		return (1);
	}
	return (0);
}

void	print_cd_error(char *str)
{
	ft_putstr_fd("shell: cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	relative_error(t_program *shell)
{
	shell->exit_code = 1;
	print_cd_error(shell->mtx_line[shell->i + 1]);
	shell->i = matrix_len(shell->mtx_line);
}
