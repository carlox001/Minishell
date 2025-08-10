/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_in_hd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 11:53:03 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/04 16:15:01 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_dollar(char *str, t_program *shell, int fd)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (exec_dollar_core(str, shell, fd, &i) == 1)
				return ;
		}
		else
		{
			ft_putchar_fd(str[i], fd);
			if (str[i] != '\0')
				i++;
		}
	}
}

int	exec_dollar_core(char *str, t_program *shell, int fd, int *i)
{
	if (str[*i] == '\0')
	{
		ft_putchar_fd('$', fd);
		return (1);
	}
	else if (str[*i] == '?')
	{
		ft_putnbr_fd(shell->exit_code, fd);
		(*i)++;
	}
	else
	{
		if (exec_dollar_core_2(shell, str, fd, i) == 1)
			return (1);
	}
	return (0);
}

int	exec_dollar_core_2(t_program *shell, char *str, int fd, int *i)
{
	int		j;
	int		len;
	char	*env_str;

	j = *i;
	len = 0;
	while (str[*i] && (ft_isalnum(str[*i]) == 1))
	{
		len++;
		(*i)++;
	}
	env_str = ft_substr(str, j, len);
	if (env_str == NULL)
		return (1);
	search_env(env_str, shell, fd);
	free(env_str);
	return (0);
}

void	search_env(char *env_str, t_program *shell, int fd)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], env_str, ft_strlen(env_str)) == 0 && \
			ft_strlen(env_str) == ft_strlen(shell->env[i]) - \
			ft_strlen(ft_strchr(shell->env[i], '=')))
		{
			while (shell->env[i][j] != '=' && shell->env[i][j])
				j++;
			j++;
			new_str = ft_substr(shell->env[i], j, ft_strlen(shell->env[i]) - j);
			ft_putstr_fd(new_str, fd);
			if (new_str == NULL)
				ft_putchar_fd('\n', fd);
			free(new_str);
		}
		i++;
	}
}
