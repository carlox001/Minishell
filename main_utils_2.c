/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cazerini <cazerini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:21:55 by sfiorini          #+#    #+#             */
/*   Updated: 2025/07/13 16:41:00 by cazerini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	permette di sistemare la gestione degli exit code
//	nelle pipes
void	set_signals_pipe(t_program *shell)
{
	if (g_signals == SIGINT)
	{
		g_signals = 0;
		if (shell->check_pipe_ex_co == 0)
			shell->exit_code = 130;
		else
			shell->check_pipe_ex_co = 0;
	}
	if (g_signals == SIGQUIT)
	{
		g_signals = 0;
		shell->exit_code = 131;
	}
}

// esegue readline e aggiunge la stringa alla history
int	readline_core(t_program *shell, char **str)
{
	char	*print_str;

	signal(SIGINT, sig_handler);
	print_str = print_directory(shell);
	shell->mtx_line = NULL;
	set_signals_pipe(shell);
	*str = readline(print_str);
	free(print_str);
	if (!(*str))
		return (printf("exit\n"), free_all(shell, 0), \
		correct_exit(shell->exit_code), 1);
	set_signals_pipe(shell);
	if (*str[0] != '\0')
		add_history((*str));
	return (0);
}

int	only_redir(char **mtx)
{
	int	i;

	i = 0;
	while (mtx[i])
	{
		if ((mtx[i][0] == '<' || mtx[i][0] == '>') && \
		mtx[i + 1] != NULL)
			i += 2;
		else
			return (0);
	}
	free_matrix(mtx);
	return (1);
}

void	search_word(char *str, int *i)
{
	while (str[*i] && str[*i] != ' ' && str[*i] != '|')
	{
		if (str[*i] == '\"')
		{
			(*i)++;
			while (str[*i] && str[*i] != '\"')
				(*i)++;
		}
		if (str[*i] == '\'')
		{
			(*i)++;
			while (str[*i] && str[*i] != '\'')
				(*i)++;
		}
		if (str[*i] != '\0')
			(*i)++;
	}
}
