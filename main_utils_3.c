/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cazerini <cazerini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:21:55 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/21 16:46:32 by cazerini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	case_space(char *str, int *i, int *init)
{
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	*init = *i;
}

void	case_pipe(int *i, int *init, int *j, char **new_mtx)
{
	new_mtx[*j] = ft_strdup("|");
	(*j)++;
	(*i)++;
	*init = *i;
}

void	update_realloc_2(char *str, int *i, int *init)
{
	while (str[*i] && (str[*i] == ' '))
		(*i)++;
	*init = *i;
}

char	**alloc_expansion(char **new_mtx, char *str, int *j)
{
	int	i;
	int	init;

	i = 0;
	init = i;
	while (str[i])
	{
		if (str[i] == ' ')
			case_space(str, &i, &init);
		else if (str[i] == '|')
			case_pipe(&i, &init, j, new_mtx);
		else
		{
			search_word(str, &i);
			if (i != init)
			{
				new_mtx[*j] = ft_substr(str, init, i - init);
				(*j)++;
			}
			update_realloc_2(str, &i, &init);
		}
	}
	return (new_mtx);
}

void	update_realloc(int j, t_program *shell, char **new_mtx)
{
	new_mtx[j] = NULL;
	free_matrix(shell->mtx_line);
	shell->mtx_line = matrix_dup(new_mtx);
	free_matrix(new_mtx);
}
