/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_handler_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:29:07 by sfiorini          #+#    #+#             */
/*   Updated: 2025/04/27 16:30:06 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	operators_core(char *str, t_program *shell, int *i, int *j)
{
	if (str[*i] == '>' && str[*i + 1] == '>')
	{
		shell->mtx_line[*j][0] = '>';
		shell->mtx_line[*j][1] = '>';
		shell->mtx_line[*j][2] = '\0';
		if (shell->i + 1 < shell->len)
			*i = *i + 2;
	}
	else if (str[*i] == '<' && str[*i + 1] == '<')
	{
		shell->mtx_line[*j][0] = '<';
		shell->mtx_line[*j][1] = '<';
		shell->mtx_line[*j][2] = '\0';
		if (shell->i + 1 < shell->len)
			*i = *i + 2;
	}
	else
		operators_core_2(str, i, j, shell);
}

void	operators_core_2(char *str, int *i, int *j, t_program *shell)
{
	if (str[*i] == '<' && str[*i + 1] == '>')
	{
		shell->mtx_line[*j][0] = '<';
		shell->mtx_line[*j][1] = '>';
		shell->mtx_line[*j][2] = '\0';
		if (shell->i + 1 < shell->len)
			*i = *i + 2;
	}
	else
	{
		shell->mtx_line[*j][0] = str[*i];
		shell->mtx_line[*j][1] = '\0';
		if (shell->i < shell->len)
			(*i)++;
	}
}

int	operators_allocation(char *str, t_program *shell, int i, int j)
{
	if ((str[i] == '>' && str[i + 1] == '>' ) || \
		(str[i] == '<' && str[i + 1] == '<' ) || \
		(str[i] == '<' && str[i + 1] == '>'))
		shell->mtx_line[j] = (char *)malloc(sizeof(char) * 3);
	else
		shell->mtx_line[j] = (char *)malloc(sizeof(char) * 2);
	if (!shell->mtx_line[j])
		return (1);
	return (0);
}
