/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 10:48:43 by cazerini          #+#    #+#             */
/*   Updated: 2025/05/09 18:16:12 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	print_too_many_arg(t_program *shell)
{
	ft_putstr_fd("shell: cd: too many arguments\n", 2);
	shell->i = matrix_len(shell->mtx_line);
	shell->exit_code = 1;
}
