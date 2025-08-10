/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cazerini <cazerini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:43:40 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/21 14:34:38 by cazerini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_shlvl(t_program *shell)
{
	int		i;
	int		value;
	char	*tmp;

	i = 0;
	value = ft_atoi(getenv("SHLVL"));
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "SHLVL=", 6) == 0)
		{
			free(shell->env[i]);
			value++;
			tmp = ft_itoa(value);
			shell->env[i] = ft_strjoin("SHLVL=", tmp);
			free(tmp);
		}
		i++;
	}
}

// restituisce il percorso della directory corrente
char	*print_directory(t_program *shell)
{
	char	*str;

	if (shell->home_path != NULL)
	{
		if (ft_strlen(shell->pwd) < ft_strlen(shell->home_path))
			str = ft_strjoin("shell:", shell->pwd);
		else
		{
			if (shell->curr_dir)
				str = ft_strjoin("shell:~", shell->curr_dir);
			else
				str = ft_strdup("shell:~");
		}
		shell->tmp = str;
		str = ft_strjoin(str, "$ ");
		free(shell->tmp);
	}
	else
	{
		str = ft_strjoin("shell:", shell->pwd);
		shell->tmp = str;
		str = ft_strjoin(str, "$ ");
		free(shell->tmp);
	}
	return (str);
}

// inizzializza il programma
int	initialize(t_program *shell)
{
	char	*str;

	shell->check_pipe_ex_co = 0;
	shell->exit_code = 0;
	shell->flag_quotes = 0;
	shell->flag_cmd_not_found = 0;
	shell->expansion_flag = 0;
	g_signals = 0;
	str = getcwd(NULL, 1000);
	shell->pwd = ft_strdup(str);
	shell->old_pwd = ft_strdup(str);
	free(str);
	str = getenv("HOME");
	if (str == NULL)
	{
		shell->home_path = NULL;
		shell->curr_dir = ft_strdup(shell->pwd);
	}
	else
	{
		shell->home_path = ft_strdup(getenv("HOME"));
		shell->curr_dir = ft_substr(shell->pwd, ft_strlen(shell->home_path), \
			(ft_strlen(shell->pwd) - ft_strlen(shell->home_path)));
	}
	return (0);
}

// libera il programma
void	free_all(t_program *shell, int flag)
{
	if (flag == 0)
	{
		if (shell->mtx_line != NULL)
			free_matrix(shell->mtx_line);
	}
	if (shell->env != NULL)
		free_matrix(shell->env);
	if (shell->pwd != NULL)
		free(shell->pwd);
	if (shell->home_path != NULL)
		free(shell->home_path);
	if (shell->curr_dir != NULL)
		free(shell->curr_dir);
	if (shell->old_pwd != NULL)
		free(shell->old_pwd);
	close(0);
	close(1);
}
