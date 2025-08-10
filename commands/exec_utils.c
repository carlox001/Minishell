/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 22:13:11 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/25 12:12:39 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	***alloc_mtx(int num_commands, t_program *shell)
{
	char	***mtx_hub;

	mtx_hub = (char ***)ft_calloc(sizeof(char **), (num_commands + 1));
	if (mtx_hub == NULL)
		return (NULL);
	alloc_mtx_core(shell, mtx_hub);
	return (mtx_hub);
}

int	alloc_mtx_core_while(t_program *shell, int *i, int *j, char ***mtx_hub)
{
	int	k;

	k = 0;
	while (shell->mtx_line[*i])
	{
		if (k == 0)
			shell->dup_mtx = (char **)ft_calloc(sizeof(char *), \
			(matrix_len(shell->mtx_line) + 1));
		if (shell->dup_mtx == NULL)
			return (1);
		if (shell->mtx_line[*i][0] == '|')
		{
			mtx_hub[*j] = matrix_dup(shell->dup_mtx);
			increments(i, j);
			free_matrix(shell->dup_mtx);
			k = 0;
		}
		else
		{
			shell->dup_mtx[k] = ft_strdup(shell->mtx_line[*i]);
			k++;
			(*i)++;
		}
	}
	return (0);
}

void	alloc_mtx_core(t_program *shell, char ***mtx_hub)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (alloc_mtx_core_while(shell, &i, &j, mtx_hub) == 1)
		return ;
	if (shell->dup_mtx[0] != NULL || shell->dup_mtx[0][0] != '\0')
	{
		mtx_hub[j] = matrix_dup(shell->dup_mtx);
		j++;
	}
	free_matrix(shell->dup_mtx);
	mtx_hub[j] = NULL;
}

int	count_commands2(t_program *shell)
{
	int		i;
	int		count;
	char	**tmp;
	int		flag;

	flag = 0;
	i = 0;
	count = 1;
	shell->flag_builtin = 0;
	tmp = alloc_builtin_mtx(shell);
	while (tmp[i])
	{
		if (flag == 0)
			flag_cmds(shell, &flag, i, tmp);
		if (tmp[i] != NULL)
			i++;
	}
	free_matrix(tmp);
	return (count);
}

int	check_flag_builtin(char **mtx, int i)
{
	if ((ft_strncmp(mtx[i], "echo", 4) == 0 && ft_strlen(mtx[i]) == 4) || \
	(ft_strncmp(mtx[i], "pwd", 3) == 0 && ft_strlen(mtx[i]) == 3) || \
	(ft_strncmp(mtx[i], "env", 3) == 0 && ft_strlen(mtx[i]) == 3) || \
	(ft_strncmp(mtx[i], "cd", 2) == 0 && ft_strlen(mtx[i]) == 2) || \
	(ft_strncmp(mtx[i], "export", 6) == 0 && ft_strlen(mtx[i]) == 6) || \
	(ft_strncmp(mtx[i], "unset", 5) == 0 && ft_strlen(mtx[i]) == 5) || \
	(ft_strncmp(mtx[i], "exit", 4) == 0 && ft_strlen(mtx[i]) == 4))
		return (1);
	return (0);
}
