/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:33:45 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/24 14:39:29 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_input(t_program *shell, int i, char ***mtx_hub, int flag)
{
	char	**tmp;

	if (shell->num_fd == -1)
		return (1);
	if (shell->num_fd > 0)
	{
		tmp = realloc_without_redir(mtx_hub[i], shell->num_fd, '<');
		if (tmp[0] == NULL)
			redir_input_clear(shell, &tmp, &mtx_hub);
		free_matrix(mtx_hub[i]);
		mtx_hub[i] = matrix_dup(tmp);
		free_matrix(tmp);
		if (flag != 1)
			dup2(shell->in[shell->num_fd - 1], STDIN_FILENO);
		close_in_out(shell->in, shell->num_fd - 1, 1);
	}
	if (mtx_hub[i][0] == NULL)
		return (1);
	return (0);
}

int	open_files_in(char **mtx, t_program *shell)
{
	int	i;
	int	j;

	i = counter_in_out('<', mtx);
	if (i == 0)
		return (0);
	shell->in = (int *)malloc(sizeof(int) * i);
	if (shell->in == NULL)
		return (-1);
	initialize_files_in(&i, &j, &shell->num_hd, 1);
	while (mtx[i])
	{
		if (open_file_in_hub(&j, &i, mtx, shell) == -1)
			return (-1);
		i++;
	}
	return (j);
}

int	open_file_in_hub(int *j, int *i, char **mtx, t_program *shell)
{
	if (mtx[*i][0] == '<' && mtx[*i][1] == '<')
	{
		if (open_file_in_hd(i, j, &shell->num_hd, shell->in) == -1)
			return (-1);
	}
	else if (mtx[*i][0] == '<' && mtx[*i][1] == '>')
	{
		shell->flag_in_operator = 1;
		if (open_file_in_fd(i, j, mtx, shell) == -1)
			return (-1);
	}
	else if (mtx[*i][0] == '<')
	{
		if (open_file_in_fd(i, j, mtx, shell) == -1)
		{
			close(shell->input);
			close(shell->output);
			free(shell->in);
			return (-1);
		}
	}
	return (0);
}

int	open_file_in_hd(int *i, int *j, int *num_hd, int *shell_in)
{
	char	*file;
	char	*tmp;

	tmp = ft_itoa(*num_hd);
	file = ft_strjoin(".here_doc_", tmp);
	shell_in[*j] = open(file, O_RDONLY, 0777);
	free(tmp);
	free(file);
	if (shell_in[*j] == -1)
	{
		free(shell_in);
		return (-1);
	}
	(*i)++;
	(*j)++;
	(*num_hd)++;
	return (0);
}

int	open_file_in_fd(int *i, int *j, char **mtx, t_program *shell)
{
	char	*tmp;

	(*i)++;
	tmp = remove_couple_quotes(mtx[(*i)]);
	if (shell->flag_in_operator == 1)
	{
		if (access(tmp, F_OK) == -1)
			shell->in[*j] = open((tmp), O_CREAT);
		else
			shell->in[*j] = open((tmp), O_RDONLY);
	}
	else
		shell->in[*j] = open((tmp), O_RDONLY);
	shell->flag_in_operator = 0;
	if (shell->in[*j] == -1)
	{
		ft_putstr_fd("shell ", 2);
		ft_putstr_fd(tmp, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(tmp);
		return (-1);
	}
	(*j)++;
	free(tmp);
	return (0);
}
