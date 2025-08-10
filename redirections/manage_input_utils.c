/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_input_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cazerini <cazerini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:33:45 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/21 12:29:24 by cazerini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir_input_clear(t_program *shell, char ***tmp, char ****mtx_hub)
{
	close_in_out(shell->in, shell->num_fd - 1, 1);
	close_in_out(shell->fd, 2, 0);
	close(shell->input);
	close(shell->output);
	free_matrix(*tmp);
	free_all(shell, 1);
	free_matrix_pointer(*mtx_hub);
	correct_exit(1);
}
