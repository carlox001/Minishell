/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:51:52 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/07 16:55:25 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_in_out(int *fd, int k, int flag)
{
	while (k >= 0)
	{
		close(fd[k]);
		k--;
	}
	if (flag == 1)
		free(fd);
}

void	close_fds(int *fd, int flag, int input)
{
	if (flag == 1)
		dup2(fd[0], STDIN_FILENO);
	else
		dup2(input, STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
}

void	close_all_files(int *fd, int output, int input)
{
	close(fd[0]);
	close(fd[1]);
	close(output);
	close(input);
}
