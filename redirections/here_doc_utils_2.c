/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:46:04 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/24 12:31:37 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_open_hd(t_program *shell, int fd, char *file, char *tmp)
{
	close(fd);
	free(file);
	free(tmp);
	shell->num_hd++;
}
