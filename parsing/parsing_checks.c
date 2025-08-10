/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:46:05 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/25 13:46:13 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	only_operator(char *str, t_program *shell)
{
	int	flag;

	shell->k = 0;
	flag = 0;
	if (ft_strlen(str) == 2)
	{
		if (str[0] == '<' && str[1] == '<')
			return (4);
		if (str[0] == '>' && str[1] == '>')
			return (4);
	}
	while (str[shell->k])
	{
		if (str[shell->k] == '|')
			flag = 1;
		if (str[shell->k] == '>')
			flag = 2;
		if (str[shell->k] == '<')
			flag = 3;
		else if (str[shell->k] != '|' && str[shell->k] != '>' && str[shell->k] \
			!= '<' && str[shell->k] != ' ' && str[shell->k] != '\0')
			return (0);
		shell->k++;
	}
	return (flag);
}

int	near_operators(char *str)
{
	int	i;
	int	op;

	i = 0;
	while (str[i])
	{
		quotes_skips(str, &i);
		op = 0;
		if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		{
			op++;
			i++;
			while ((str[i] == '|' || str[i] == '<' || str[i] \
				== '>' || str[i] == ' ') && str[i])
				near_operators_core(str, &i, &op);
			if (op > 2)
				return (1);
		}
		if (str[i] != '\0')
			i++;
	}
	return (0);
}

void	near_operators_core(char *str, int *i, int *op)
{
	if (str[*i] != ' ')
	{
		if (str[*i] == '>')
		{
			(*i)++;
			(*op)++;
			if (str[*i] == '>')
				(*i)++;
		}
		else if (str[*i] == '<')
		{
			(*i)++;
			(*op)++;
			if (str[*i] == '<')
				(*i)++;
		}
		else
		{
			(*op)++;
			(*i)++;
		}
	}
	else
		(*i)++;
}

int	check_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				i++;
			if (str[i] == '\0')
				return (1);
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (str[i] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}
