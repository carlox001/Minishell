/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:15:02 by sfiorini          #+#    #+#             */
/*   Updated: 2025/04/27 16:51:56 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_internal_quotes(char *old_str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	if ((old_str[i] == '\'' || old_str[i] == '"'))
		i = 1;
	j = 0;
	while (old_str[i] && i < ((int)ft_strlen(old_str)))
	{
		if ((old_str[i] == '\'' || old_str[i] == '"'))
			j++;
		i++;
	}
	if (old_str[(int)ft_strlen(old_str) - 1] == '"' || \
		old_str[(int)ft_strlen(old_str) - 1] == '\'')
		j--;
	new_str = remove_internal_quotes_core(old_str, i, &j);
	if (new_str == NULL)
		return (NULL);
	new_str[j] = '\0';
	return (new_str);
}

char	*remove_internal_quotes_core(char *old_str, int i, int *j)
{
	char	*new_str;

	new_str = (char *)malloc(sizeof(char) * (i - (*j) + 1));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	(*j) = 0;
	while (old_str[i] && i < ((int)ft_strlen(old_str)))
	{
		if (i == 0 || i == (int)ft_strlen(old_str) - 1)
		{
			new_str[(*j)] = old_str[i];
			i++;
			(*j)++;
		}
		else if ((old_str[i] == '\'' || old_str[i] == '"'))
			i++;
		else
		{
			new_str[(*j)] = old_str[i];
			i++;
			(*j)++;
		}
	}
	return (new_str);
}

char	*remove_all_quotes(char *old_str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (old_str[i] && i < ((int)ft_strlen(old_str)))
	{
		if ((old_str[i] == '\'' || old_str[i] == '"'))
			j++;
		i++;
	}
	new_str = remove_all_quotes_core(old_str, i, j);
	if (new_str == NULL)
		return (NULL);
	return (new_str);
}

char	*remove_all_quotes_core(char *old_str, int i, int j)
{
	char	*new_str;

	new_str = (char *)malloc(sizeof(char) * (i - j + 1));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (old_str[i] && i < ((int)ft_strlen(old_str)))
	{
		if ((old_str[i] == '\'' || old_str[i] == '"'))
			i++;
		else
		{
			new_str[j] = old_str[i];
			i++;
			j++;
		}
	}
	new_str[j] = '\0';
	return (new_str);
}
