/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:46:04 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/24 15:15:59 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_hd_g_signals(int flag)
{
	if (flag == 1)
	{
		signal(SIGQUIT, sig_handler_hd);
		signal(SIGINT, sig_handler_hd);
	}
	else
	{
		signal(SIGQUIT, sig_handler_child);
		signal(SIGINT, sig_handler);
	}
}

void	close_here_doc(t_program *shell)
{
	int		i;
	char	*num;
	char	*file;
	int		flag;
	int		fd;

	i = 0;
	flag = 0;
	while (flag == 0)
	{
		num = ft_itoa(i);
		file = ft_strjoin(".here_doc_", num);
		fd = open(file, O_RDONLY);
		if (fd == -1)
			flag = 1;
		else
		{
			close(fd);
			unlink(file);
		}
		free(file);
		free(num);
		i++;
	}
	shell->num_hd = 0;
}

int	else_here_doc(t_program *shell, int id)
{
	waitpid(id, &shell->num_hd, 0);
	shell->num_hd /= 256;
	if (shell->num_hd == 255)
	{
		shell->exit_code = 0;
		return (-2);
	}
	if (g_signals == 2)
	{
		shell->exit_code = 130;
		close_here_doc(shell);
		return (-2);
	}
	return (0);
}

void	false_heredoc(t_program *shell, char *str)
{
	matrix_handler(str, shell);
	open_here_doc(shell, shell->mtx_line);
	close_here_doc(shell);
	free_matrix(shell->mtx_line);
}

int	is_there_a_single_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}
