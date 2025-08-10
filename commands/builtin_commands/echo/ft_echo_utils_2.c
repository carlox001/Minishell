/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cazerini <cazerini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:16:28 by cazerini          #+#    #+#             */
/*   Updated: 2025/05/21 18:22:11 by cazerini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	get_printable_echo_str(char **str2, t_program *shell)
{
	char	*str;
	int		flag;

	str = ft_strdup(shell->mtx_line[shell->i + 1]);
	if (only_quotes(str, &flag) == 0)
		return (free(str), 1);
	*str2 = ft_strdup(str);
	if (*str2 == NULL)
		*str2 = ft_strdup(str);
	free(str);
	return (0);
}

int	counter_quotes(char *old_str, char q)
{
	int	counter;
	int	i;

	counter = 0;
	i = 0;
	while (old_str[i])
	{
		if (old_str[i] == q)
			counter++;
		i++;
	}
	return (counter);
}

void	rem_quote_case(char *old_str, int *i, char **new_str, char q)
{
	int		init;
	char	*tmp;
	char	*sub_str;
	int		flag;

	init = *i;
	sub_str = NULL;
	flag = 0;
	while (old_str[*i] && old_str[*i] != q)
		(*i)++;
	if (only_quotes(old_str, &flag) == 0)
		alloc_only_quote(&sub_str, flag);
	else
		sub_str = ft_substr(old_str, init, *i - init);
	if (*new_str == NULL)
		*new_str = ft_strdup(sub_str);
	else
	{
		tmp = *new_str;
		*new_str = ft_strjoin(*new_str, sub_str);
		free(tmp);
	}
	free(sub_str);
	if (old_str[*i] != '\0')
		(*i)++;
}

void	rem_null_char(char *old_str, int *i, char **new_str)
{
	char	*tmp;
	char	*str_add;

	if (*new_str == NULL)
	{
		str_add = ft_substr(old_str, *i, 1);
		*new_str = ft_strdup(str_add);
		free(str_add);
	}
	else
	{
		str_add = ft_substr(old_str, *i, 1);
		tmp = *new_str;
		*new_str = ft_strjoin(*new_str, str_add);
		free(tmp);
		free(str_add);
	}
	(*i)++;
}

char	*remove_couple_quotes(char *old_str)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = NULL;
	while (old_str[i])
	{
		if (old_str[i] == '\'')
		{
			i++;
			rem_quote_case(old_str, &i, &new_str, '\'');
		}
		else if (old_str[i] == '\"')
		{
			i++;
			rem_quote_case(old_str, &i, &new_str, '\"');
		}
		else if (old_str[i] != '\0')
			rem_null_char(old_str, &i, &new_str);
	}
	if (new_str == NULL)
		new_str = ft_strdup(old_str);
	return (new_str);
}
