/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cazerini <cazerini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:16:28 by cazerini          #+#    #+#             */
/*   Updated: 2025/05/21 18:29:06 by cazerini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	ft_echo(t_program *shell)
{
	int		i;
	int		len;
	char	*str2;

	if (shell->mtx_line[shell->i + 1] == NULL)
	{
		printf("\n");
		shell->exit_code = 0;
		return ;
	}
	check_nflag(shell->mtx_line, shell);
	len = count_args(shell->mtx_line, shell->i + 1);
	i = 0;
	while (i < len)
	{
		if (get_printable_echo_str(&str2, shell) == 0)
			echo_if(shell, &str2, &i, len);
		else
		{
			i++;
			shell->i++;
		}
	}
	if (shell->nflag != 1)
		printf("\n");
}

void	ft_echo_core(t_program *shell, char *str2, int *i, int len)
{
	if (str2[0] != '>')
	{
		if (str2)
			ft_echo_core_2(str2, i, shell, len);
	}
	else
	{
		(*i)++;
		shell->i++;
		if (shell->mtx_line[shell->i + 1] != NULL)
		{
			(*i)++;
			shell->i++;
		}
	}
	free(str2);
	(*i)++;
	shell->i++;
	shell->exit_code = 0;
}

void	ft_echo_core_2(char *str2, int *i, t_program *shell, int len)
{
	if (*i != len - 1)
	{
		if (str2[0] == '$' && str2[1] == '?')
		{
			printf("%d ", shell->exit_code);
			shell->i++;
		}
		else
			printf("%s ", str2);
	}
	else
	{
		if (str2[0] == '$' && str2[1] == '?')
		{
			printf("%d", shell->exit_code);
			shell->i++;
		}
		else
			printf("%s", str2);
	}
}

int	count_couple_quotes(char *old_str, char q)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (old_str[i])
	{
		if (old_str[i] == q)
		{
			i++;
			while (old_str[i] && old_str[i] != q)
			{
				i++;
				count++;
			}
		}
		if (old_str[i] != '\0')
			i++;
		count++;
	}
	return (count);
}
