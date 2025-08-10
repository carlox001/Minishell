/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 13:52:42 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/24 11:32:51 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

//problema in matrix handler quando si va a scrivere tipo : export d
// famo gli exit code
void	ft_export(t_program *shell)
{
	int		i;
	int		value;
	int		j;
	char	*str;
	char	*dup;

	if (only_export(shell) == 1)
		return ;
	j = 1;
	while (shell->mtx_line[shell->i + j])
	{
		if (export_parsing(shell, j) != 1)
		{
			i = 0;
			dup = ft_strdup(shell->mtx_line[shell->i + j]);
			str = remove_couple_quotes(dup);
			free(dup);
			value = 0;
			i = export_cicle(str);
			export_core(shell, value, i, str);
		}
		j++;
	}
	shell->i += j;
}

int	export_cicle(char *str)
{
	int		i;
	char	*dup;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (str[i] == '>' || str[i] == '<')
		{
			dup = str;
			str = ft_substr(str, 0, i);
			free(dup);
			break ;
		}
		else
			i++;
	}
	return (i);
}

int	exist_in_env(char *str, t_program *shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	shell->equal = 0;
	while (str[j])
	{
		if (str[j] == '=')
		{
			shell->equal = 1;
			break ;
		}
		j++;
	}
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], str, j) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	print_export_env(t_program *shell, int i, int j)
{
	printf("declare -x ");
	while (shell->cpy_exp[i][j])
	{
		while (shell->cpy_exp[i][j] && shell->cpy_exp[i][j] != '=')
		{
			printf("%c", shell->cpy_exp[i][j]);
			j++;
		}
		if (shell->cpy_exp[i][j] == '=')
		{
			j++;
			printf("=\"");
			while (shell->cpy_exp[i][j])
			{
				printf("%c", shell->cpy_exp[i][j]);
				j++;
			}
			printf("\"\n");
		}
		else
			printf("\n");
	}
}

void	export_core(t_program *shell, int value, int i, char *str)
{
	shell->flag = 0;
	value = is_there_in_env(shell, i, str, &shell->flag);
	if (value == -3)
		return (free(str));
	else if (value >= 0)
		change_export_value(shell, i, value, str);
	else
	{
		if (there_is_a_plus(str) == 1)
			update_plus(&str);
		if (realloc_env(shell, str) == 1)
			return ;
	}
}
