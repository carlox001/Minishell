/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:11:30 by cazerini          #+#    #+#             */
/*   Updated: 2025/05/24 11:37:47 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	print_unset_error(char *str)
{
	ft_putstr_fd("shell: unset: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	unset_parsing(t_program *shell, int j)
{
	char	*str;
	int		check;

	str = remove_couple_quotes(shell->mtx_line[shell->i + j]);
	check = unset_parsing_2(shell, str);
	if (check == 1)
		return (free(str), 1);
	if (unset_parsing_quote(str) == 1)
	{
		print_unset_error(str);
		shell->exit_code = 1;
		free(str);
		return (1);
	}
	free(str);
	return (0);
}

int	unset_parsing_2(t_program *shell, char *str)
{
	shell->k = 0;
	if (str[0] == '=' || (ft_isalpha(str[0]) != 1 && str[0] != '_' && \
		str[0] != '\'' && str[0] != '"' && str[0] != '/'))
	{
		print_unset_error(str);
		shell->exit_code = 1;
		return (1);
	}
	while (str[shell->k])
	{
		if (ft_isalnum(str[shell->k]) != 1 && str[shell->k] != '_' && \
			str[shell->k] != '\'' && str[shell->k] != '"')
		{
			print_unset_error(str);
			shell->exit_code = 1;
			return (1);
		}
		shell->k++;
	}
	return (0);
}

int	unset_parsing_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'' || str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
