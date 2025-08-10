/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:21:55 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/25 12:00:19 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_program	shell;

	(void)ac;
	(void)av;
	shell.env = matrix_dup(env);
	shell.fork_id = -2;
	shell.flag_in_operator = 0;
	update_shlvl(&shell);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	if (main_core(&shell) == 1)
		return (1);
	return (0);
}

void	correct_here_doc(t_program *shell)
{
	int		i;
	int		counter;
	char	*tmp;

	i = 0;
	counter = 0;
	while (shell->mtx_line[i])
	{
		if (shell->mtx_line[i][0] == '<' && shell->mtx_line[i][1] == '<')
		{
			free(shell->mtx_line[i]);
			free(shell->mtx_line[i + 1]);
			tmp = ft_itoa(counter);
			shell->mtx_line[i] = ft_strdup("<");
			shell->mtx_line[i + 1] = ft_strjoin(".here_doc_", tmp);
			counter++;
			free(tmp);
		}
		if (shell->mtx_line[i] != NULL)
			i++;
	}
}

int	flag_hd_decision(t_program *shell, int flag)
{
	if (flag > 0)
		correct_here_doc(shell);
	if (flag == -1)
		return (free_all(shell, 0), 1);
	else if (flag != -2 && main_core_2(shell) == 1)
		return (1);
	else if (flag == -2)
		free_matrix(shell->mtx_line);
	return (0);
}

int	main_core(t_program *shell)
{
	char	*str;
	int		flag;

	if (initialize(shell) == 1)
		return (1);
	str = NULL;
	while (1)
	{
		if (readline_core(shell, &str) == 1)
			return (1);
		flag = parsing(str, shell);
		if (flag == 0)
			false_heredoc(shell, str);
		free(str);
		if (flag != 0)
		{
			realloc_expansion(shell);
			signal(SIGINT, sig_handler_child);
			signal(SIGQUIT, sig_handler);
			flag = open_here_doc(shell, shell->mtx_line);
			if (flag_hd_decision(shell, flag) == 1)
				return (1);
		}
	}
	return (0);
}

int	main_core_2(t_program *shell)
{
	if (only_redir(shell->mtx_line) == 1)
	{
		shell->exit_code = 0;
		close_here_doc(shell);
	}
	else if (exec(shell) == 1)
		return (free_all(shell, 0), 1);
	return (0);
}
