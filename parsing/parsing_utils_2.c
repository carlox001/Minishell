/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cazerini <cazerini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:04:25 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/23 18:07:22 by cazerini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	end_expansion2(t_program *shell, char *old_str, int *i, char **new_str)
{
	int	len;

	len = 0;
	while (old_str[*i + len] && old_str[*i + len] != '\"' && \
		old_str[*i + len] != '\'' && old_str[*i + len] != '$' && \
		old_str[*i + len] != ' ')
		len++;
	shell->sub_str = ft_substr(old_str, *i, len);
	shell->path_expansion = ft_getenv(shell, &shell->sub_str);
	path_fuond(&shell->path_expansion, new_str);
	free(shell->path_expansion);
	free(shell->sub_str);
	*i += len;
}

int	first_expansion2_check(char *old_str, int *i)
{
	while (old_str[(*i)] && old_str[(*i)] == '$')
		(*i)++;
	if (((old_str[(*i)] == '\"' && old_str[(*i) + 1] == '\"' ) || \
	(old_str[(*i)] == '\'' && old_str[(*i) + 1] == '\'' )) && \
	ft_strlen(old_str) == 3)
		return (1);
	return (0);
}

void	else_expansion_variable2_core(char **new_str, char *tmp)
{
	char	*tmp2;

	tmp2 = *new_str;
	*new_str = ft_strjoin(*new_str, tmp);
	free(tmp2);
}

int	expansion_variable2_core(t_program *shell, int *i, \
char *old_str, char **new_str)
{
	char	*tmp;

	if (first_expansion2_check(old_str, i) == 1)
		return (1);
	else if (old_str[*i] == '\0')
		*new_str = ft_strdup("\"\"");
	else if (old_str[*i] == '?')
	{
		tmp = ft_itoa(shell->exit_code);
		if (*new_str == NULL)
			*new_str = ft_strdup(tmp);
		else
			else_expansion_variable2_core(new_str, tmp);
		free(tmp);
		(*i)++;
	}
	else
		end_expansion2(shell, old_str, i, new_str);
	return (0);
}

//se null rialloca shiftando i null
char	*expansion_variable2(char *old_str, t_program *shell)
{
	char	*new_str;
	int		i;
	int		flag;
	int		flag_d;

	if (only_dollar(old_str) == 1)
		return (ft_strdup(old_str));
	i = 0;
	new_str = NULL;
	flag = 0;
	flag_d = 0;
	while (old_str[i])
	{
		check_flag(&flag, &flag_d, old_str[i]);
		if (old_str[i] == '$' && old_str[i + 1] != '\0' \
			&& old_str[i + 1] != ' ' && old_str[i + 1] != '\'' \
			&& flag == 0)
		{
			if (expansion_variable2_core(shell, &i, old_str, &new_str) == 1)
				return (ft_strdup("\" \""));
		}
		else
			expansion_variable2_else(&i, old_str, &new_str);
	}
	return (new_str);
}
