/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:49:48 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/19 18:23:09 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_words(char *str, t_program *shell)
{
	int	words;
	int	flag;

	shell->len = (int)ft_strlen(str);
	shell->i = 0;
	flag = 0;
	words = 0;
	while (str[shell->i] && str[shell->i] == ' ')
		shell->i++;
	while (str[shell->i])
	{
		while (str[shell->i] && str[shell->i] != ' ')
		{
			flag = 1;
			if (str[shell->i] == '\'')
				skip_quote(shell, str, '\'');
			if (str[shell->i] == '\"')
				skip_quote(shell, str, '\"');
			operator_count(shell, str, &words);
			continue_count(shell, str, &flag, &words);
		}
		if (str[shell->i] != '\0')
			shell->i++;
	}
	return (words);
}

void	skip_quote(t_program *shell, char *str, char q)
{
	shell->i++;
	while (str[shell->i] && str[shell->i] != q)
		shell->i++;
}

void	continue_count(t_program *shell, char *str, int *flag, int *words)
{
	if (str[shell->i] != '\0')
		shell->i++;
	if (*flag == 1)
	{
		(*words)++;
		*flag = 0;
	}
	if (str[shell->i] != '\0')
		shell->i++;
}

void	operator_count(t_program *shell, char *str, int *words)
{
	if (str[shell->i] == '>' || str[shell->i] == '<' || \
		str[shell->i] == '|')
	{
		if (str[shell->i + 1] == '>' || \
			str[shell->i + 1] == '<')
			shell->i++;
		(*words)++;
	}
}

int	isvalid(char *str, int i)
{
	if ((str[i]) && ((str[i] >= 33 && str[i] < 127) && str[i] && \
		(str[i] != '|' && str[i] != '>' && str[i] != '<' && \
		str[i] != '"' && str[i] != '\'')))
		return (1);
	return (0);
}
