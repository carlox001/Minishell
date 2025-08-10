/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_commands_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:32:04 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/24 13:10:13 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_access(char *path, int flag)
{
	if (access(path, F_OK) == 0 && access(path, X_OK) == 0 && \
		flag == 0)
		return (1);
	return (0);
}
