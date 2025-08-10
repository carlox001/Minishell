/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:17:19 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/25 13:47:47 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	numeric_argument(t_program *shell, char ***mtx_hub)
{
	ft_putstr_fd("shell: exit: ", 2);
	ft_putstr_fd(shell->mtx_line[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	close(shell->input);
	close(shell->output);
	free_all(shell, 0);
	free_matrix_pointer(mtx_hub);
	exit(2);
}

int	is_there_an_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(t_program *shell, char ***mtx_hub)
{
	int					value;
	long long			num;

	printf("exit\n");
	if (shell->mtx_line[1] == NULL)
	{
		close(shell->input);
		close(shell->output);
		free_all(shell, 0);
		free_matrix_pointer(mtx_hub);
		correct_exit(0);
	}
	num = ft_atol(shell->mtx_line[1]);
	value = 0;
	if (ft_strlen(shell->mtx_line[1]) > 19 || num >= LONG_MAX)
		numeric_argument(shell, mtx_hub);
	else
		value = exit_core(shell, mtx_hub);
	if (value != 1)
		free_all(shell, 0);
}

int	exit_core(t_program *shell, char ***mtx_hub)
{
	int				i;
	unsigned char	*tmp;

	i = 0;
	if (shell->mtx_line[1][i] == '+' || shell->mtx_line[1][i] == '-')
		i++;
	is_valid_exit(shell, &i, mtx_hub);
	if (matrix_len(shell->mtx_line) > 2)
	{
		ft_putstr_fd("shell: exit: too many arguments\n", 2);
		shell->exit_code = 1;
		return (1);
	}
	i = ft_atoi(shell->mtx_line[1]);
	tmp = (unsigned char *)ft_itoa(i);
	i = ft_atoi((const char *)tmp);
	close(shell->input);
	close(shell->output);
	free(tmp);
	free_matrix_pointer(mtx_hub);
	free_all(shell, 0);
	correct_exit(i);
	return (0);
}

void	is_valid_exit(t_program *shell, int *i, char ***mtx_hub)
{
	while (shell->mtx_line[1][*i])
	{
		if (ft_isalpha(shell->mtx_line[1][*i]) == 1)
		{
			ft_putstr_fd("shell: exit: ", 2);
			ft_putstr_fd(shell->mtx_line[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			close(shell->input);
			close(shell->output);
			free_all(shell, 0);
			free_matrix_pointer(mtx_hub);
			exit(2);
		}
		(*i)++;
	}
}
