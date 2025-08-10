/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cazerini <cazerini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:04:25 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/23 11:54:09 by cazerini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	static_check(char **old_str, int *i, char **new_str)
{
	if (*old_str[*i] && ((*old_str[*i] == '\"' && *old_str[*i + 1] == '\"' ) || \
		(*old_str[*i] == '\'' && *old_str[*i + 1] == '\'' )) && \
		ft_strlen(*old_str) == 3)
		return (1);
	if (*old_str[*i] == '\0')
	{
		*new_str = ft_strdup("\"\"");
		return (0);
	}
	if (*old_str[*i] == '?')
		return (2);
	return (0);
}

void	path_fuond(char **path, char **new_str)
{
	char	*tmp;

	if (*path != NULL)
	{
		if (*new_str == NULL)
			*new_str = ft_strdup(*path);
		else
		{
			tmp = *new_str;
			*new_str = ft_strjoin(*new_str, *path);
			free(tmp);
		}
	}
}

void	expansion_variable2_else(int *i, char *old_str, char **new_str)
{
	char	*tmp;
	char	*chr;

	chr = (char *)malloc(sizeof(char) * 2);
	chr[0] = old_str[*i];
	chr[1] = '\0';
	if (*new_str == NULL)
		*new_str = ft_strdup(chr);
	else
	{
		tmp = *new_str;
		*new_str = ft_strjoin(*new_str, chr);
		free(tmp);
	}
	free(chr);
	(*i)++;
}

char	*ft_getenv(t_program *shell, char **sub_str)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(*sub_str, shell->env[i], ft_strlen(*sub_str)) == 0 && \
		shell->env[i][ft_strlen(*sub_str)] == '=')
			return (ft_substr(shell->env[i], (ft_strlen(*sub_str) + 1), \
			ft_strlen(shell->env[i]) - (ft_strlen(*sub_str) + 1)));
		i++;
	}
	return (NULL);
}

int	only_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
