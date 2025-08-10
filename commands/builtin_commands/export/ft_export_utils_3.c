/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:45:53 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/19 17:50:27 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	**order_env(t_program *shell)
{
	char	**export;
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = -1;
	export = matrix_dup(shell->env);
	while (++j < matrix_len(shell->env))
	{
		i = 0;
		while (i < matrix_len(shell->env) - 1)
		{
			if (ft_strncmp(export[i], export[i + 1], ft_strlen(export[i])) >= 0)
			{
				tmp = export[i];
				export[i] = ft_strdup(export[i + 1]);
				free(export[i + 1]);
				export[i + 1] = ft_strdup(tmp);
				free(tmp);
			}
			i++;
		}
	}
	return (export);
}

void	print_export_error(char *str)
{
	ft_putstr_fd("shell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	there_is_a_plus(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+')
			return (1);
		i++;
	}
	return (0);
}

void	update_plus(char **str)
{
	char	*tmp;

	tmp = *str;
	*str = remove_plus(*str);
	free(tmp);
}
