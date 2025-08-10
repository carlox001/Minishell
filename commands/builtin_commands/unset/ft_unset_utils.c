/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:16:32 by cazerini          #+#    #+#             */
/*   Updated: 2025/05/04 18:00:32 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*search_unset(t_program *shell, int l)
{
	int	j;

	j = 0;
	while (j < matrix_len(shell->env))
	{
		if (ft_strncmp(shell->env[j], shell->mtx_line[shell->i + l], \
		ft_strlen(shell->mtx_line[shell->i + l])) == 0)
			return (ft_strdup(shell->env[j]));
		j++;
	}
	return (NULL);
}

void	arg_treatment(t_program *shell, char *arg, int k, int j)
{
	char	**env_tmp;

	env_tmp = (char **)ft_calloc(sizeof(char *), (matrix_len(shell->env) + 1));
	if (env_tmp == NULL)
		return ;
	while (shell->env[k])
	{
		if (ft_strncmp(shell->env[k], arg, ft_strlen(arg)) != 0)
		{
			env_tmp[j] = ft_strdup(shell->env[k]);
			j++;
		}
		k++;
	}
	env_tmp[j] = NULL;
	free_matrix(shell->env);
	shell->env = matrix_dup(env_tmp);
	free_matrix(env_tmp);
	if (arg != NULL)
		free(arg);
}

char	*split_dollar(char *old_str, t_program *shell)
{
	char	*new_str;
	char	**mtx;
	int		flag;

	if (old_str[0] == '$')
		flag = 1;
	else
		flag = 0;
	mtx = ft_split(old_str, '$');
	if (mtx == NULL)
		return (NULL);
	first_split_dollar_loop(mtx, shell, flag);
	second_split_dollar_loop(&new_str, mtx);
	free_matrix(mtx);
	return (new_str);
}

void	first_split_dollar_loop(char **mtx, t_program *shell, int flag)
{
	int		i;
	char	*tmp;

	i = 0;
	while (mtx[i])
	{
		if (!(flag == 1 && i == 0))
		{
			tmp = mtx[i];
			mtx[i] = expansion_variable(mtx[i], shell);
			if (mtx[i] == NULL)
				return (free_matrix(mtx));
			free(tmp);
		}
		i++;
	}
}

void	second_split_dollar_loop(char **new_str, char **mtx)
{
	int		i;
	char	*tmp;

	i = 1;
	*new_str = ft_strdup(mtx[0]);
	while (mtx[i])
	{
		if (mtx[i] != NULL)
		{
			tmp = *new_str;
			*new_str = ft_strjoin(*new_str, mtx[i]);
			free(tmp);
		}
		i++;
	}
}
