/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cazerini <cazerini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:21:55 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/21 16:48:45 by cazerini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	realloc_expansion(t_program *shell)
{
	char	**new_mtx;
	int		i;
	int		j;

	shell->words = 0;
	i = -1;
	while (shell->mtx_line[++i])
		shell->words += count_words(shell->mtx_line[i], shell);
	new_mtx = (char **)malloc(sizeof(char *) * (shell->words + 1));
	if (new_mtx == NULL)
		return ;
	i = 0;
	j = 0;
	while (shell->mtx_line[i])
	{
		if (need_to_correct_expansion(shell->mtx_line[i]) == 1)
			new_mtx = alloc_expansion(new_mtx, shell->mtx_line[i], &j);
		else
		{
			new_mtx[j] = ft_strdup(shell->mtx_line[i]);
			j++;
		}
		i++;
	}
	update_realloc(j, shell, new_mtx);
}

void	skip_quotes(char *str, int *i)
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
}

int	need_to_correct_expansion(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '|' && str[i + 1] == '\0')
		return (0);
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i])
	{
		skip_quotes(str, &i);
		if (str[i] == ' ' || str[i] == '|')
		{
			while (str[i] && str[i] == ' ' && str[i] != '|')
				i++;
			if (str[i] != '\0' || str[i] == '|')
				return (1);
		}
		if (str[i] != '\0')
			i++;
	}
	return (0);
}
