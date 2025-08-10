/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_builtin_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:17:19 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/24 10:59:41 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(t_program *shell)
{
	char	*buffer;

	buffer = getcwd(NULL, 4096);
	if (!buffer)
		return (1);
	printf("%s\n", buffer);
	free(buffer);
	shell->exit_code = 0;
	return (0);
}

int	ft_env(t_program *shell)
{
	int	i;

	if (shell->mtx_line[1] != NULL)
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(shell->mtx_line[1], 2);
		ft_putstr_fd("': No such file or directory\n", 2);
		shell->exit_code = 127;
		shell->i = matrix_len(shell->mtx_line);
		return (0);
	}
	i = 0;
	while (shell->env[i])
	{
		if (is_there_an_equal(shell->env[i]) == 1)
			printf("%s\n", shell->env[i]);
		i++;
	}
	shell->exit_code = 0;
	return (0);
}
