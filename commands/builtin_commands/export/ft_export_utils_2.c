/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:16:08 by cazerini          #+#    #+#             */
/*   Updated: 2025/05/24 11:35:25 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	only_export(t_program *shell)
{
	int	i;
	int	j;

	i = 0;
	if (shell->mtx_line[shell->i + 1] == NULL)
	{
		shell->cpy_exp = order_env(shell);
		while (shell->cpy_exp[i])
		{
			j = 0;
			print_export_env(shell, i, j);
			i++;
		}
		free_matrix(shell->cpy_exp);
		return (1);
	}
	return (0);
}

// esegue del parsing aggiuntivo peril comando export
int	export_parsing(t_program *shell, int j)
{
	char	*str;
	int		check;

	str = remove_couple_quotes(shell->mtx_line[shell->i + j]);
	check = export_parsing_2(shell, str);
	if (check == 1)
		return (free(str), 1);
	if (export_parsing_quote(str) == 1)
	{
		print_export_error(str);
		shell->exit_code = 1;
		free(str);
		return (1);
	}
	free(str);
	return (0);
}

int	export_parsing_2(t_program *shell, char *str)
{
	shell->k = 0;
	if (str[0] == '=' || (ft_isalpha(str[0]) != 1 && str[0] != '_' && \
		str[0] != '\'' && str[0] != '"' && str[0] != '/'))
	{
		print_export_error(str);
		shell->exit_code = 1;
		return (1);
	}
	while (str[shell->k] != '=' && str[shell->k])
	{
		if (str[shell->k] == '+' && str[shell->k + 1] == '=')
			break ;
		if (ft_isalnum(str[shell->k]) != 1 && str[shell->k] != '_' && \
			str[shell->k] != '\'' && str[shell->k] != '"')
		{
			print_export_error(str);
			shell->exit_code = 1;
			return (1);
		}
		shell->k++;
	}
	return (0);
}

int	export_parsing_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '\"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}
