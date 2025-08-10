/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cazerini <cazerini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 13:55:44 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/23 13:43:59 by cazerini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	is_there_in_env(t_program *shell, int len, char *str, int *flag)
{
	int		value;
	char	*dup;

	if (exist_in_env(str, shell) == 1 && shell->equal == 0)
		return (-3);
	if (str[0] == '+')
		return (-3);
	if (len >= 2 && str[len - 1] == '+')
	{
		(*flag) = 1;
		dup = remove_plus(str);
		len--;
	}
	else
		dup = ft_strdup(str);
	value = replace(shell, len, dup);
	return (value);
}

int	replace(t_program *shell, int len, char *dup)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], dup, len) == 0)
			return (free(dup), i);
		i++;
	}
	free(dup);
	return (-1);
}

char	*remove_plus(char *old_str)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = (char *)malloc(sizeof(char) * ft_strlen(old_str));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (old_str[i])
	{
		if (old_str[i] == '+')
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

// cambia il valore inserito all'interno 
// di env senza la riallocazione
void	change_export_value(t_program *shell, int i, int value, char *str)
{
	char	*dup2;
	char	*dup;

	if (shell->flag == 1)
	{
		dup = ft_strdup(shell->env[value]);
		if (is_there_an_equal(shell->env[value]) == 1)
			dup2 = ft_substr(str, i + 1, ft_strlen(str) - i);
		else
			dup2 = ft_substr(str, i, ft_strlen(str) - i);
		free(shell->env[value]);
		shell->env[value] = ft_strjoin(dup, dup2);
		free(str);
		free(dup);
		free(dup2);
	}
	else
	{
		free(shell->env[value]);
		shell->env[value] = ft_strdup(str);
		free(str);
	}
}

// rialloca env poiche' la nuova stringa non esiste
int	realloc_env(t_program *shell, char *str)
{
	char	**mtx_dup;
	int		i;

	mtx_dup = matrix_dup(shell->env);
	if (mtx_dup == NULL)
		return (1);
	free_matrix(shell->env);
	shell->env = (char **)malloc(sizeof(char *) * (matrix_len(mtx_dup) + 2));
	if (shell->env == NULL)
		return (1);
	i = 0;
	while (mtx_dup[i])
	{
		shell->env[i] = ft_strdup(mtx_dup[i]);
		i++;
	}
	shell->env[i] = ft_strdup(str);
	free(str);
	shell->env[i + 1] = NULL;
	free_matrix(mtx_dup);
	return (0);
}
