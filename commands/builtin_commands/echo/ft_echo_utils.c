/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cazerini <cazerini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:16:28 by cazerini          #+#    #+#             */
/*   Updated: 2025/05/21 17:45:37 by cazerini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*remove_external_quotes(char *old_str, char q)
{
	int		count_left;
	int		count_right;
	int		i;
	char	*new_str;

	i = 0;
	count_left = 0;
	count_right = 0;
	while (old_str[i] == q)
	{
		i++;
		count_left++;
	}
	i = ft_strlen(old_str) - 1;
	while (old_str[i] == q)
	{
		i--;
		count_right++;
	}
	new_str = remove_external_quotes_core(old_str, count_left, count_right, i);
	if (new_str == NULL)
		return (NULL);
	return (new_str);
}

char	*remove_external_quotes_core(char *old_str, int c_l, int c_r, int i)
{
	char	*new_str;
	int		j;
	int		len;

	if (c_l == 0 || c_r == 0)
		return (NULL);
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(old_str) + 1 \
	- (c_l + c_r)));
	if (new_str == NULL)
		return (NULL);
	i = c_l;
	j = 0;
	len = (int)ft_strlen(old_str);
	while (i < (len - c_r))
	{
		new_str[j] = old_str[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}

int	count_args(char **mtx, int i)
{
	int	len;

	len = 0;
	while (mtx[i] && mtx[i][0] != '|')
	{
		len++;
		i++;
	}
	return (len);
}

void	check_nflag(char **mtx, t_program *shell)
{
	int		i;
	char	*str;

	shell->nflag = 0;
	str = NULL;
	while (mtx[shell->i + 1])
	{
		str = remove_couple_quotes(mtx[shell->i + 1]);
		i = 0;
		if (str[i] == '-')
		{
			i++;
			while (str[i] && str[i] == 'n')
				i++;
			if (str[i] != 'n' && str[i] != '\0')
				return (free(str));
			shell->i++;
			shell->nflag = 1;
		}
		else
			return (free(str));
		free(str);
	}
}

// 1: trova dollar
// 0: non trova
int	check_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
