/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cazerini <cazerini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 22:13:11 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/23 18:03:41 by cazerini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	increments(int *i, int *j)
{
	(*j)++;
	(*i)++;
}

void	set_exec_signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	update_counter_exec(int *j, int *i)
{
	(*j)--;
	(*i)++;
}

void	free_matrix_pointer(char ***mtx_hub)
{
	int	i;

	i = 0;
	while (mtx_hub[i])
	{
		free_matrix(mtx_hub[i]);
		i++;
	}
	free(mtx_hub);
}

char	**alloc_builtin_mtx(t_program *shell)
{
	char	**dup;
	int		i;

	i = 0;
	dup = (char **)malloc(sizeof(char *) * (matrix_len(shell->mtx_line) + 1));
	if (dup == NULL)
		return (NULL);
	while (shell->mtx_line[i])
	{
		dup[i] = remove_couple_quotes(shell->mtx_line[i]);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
