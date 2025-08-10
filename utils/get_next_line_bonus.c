/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:59:08 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/24 10:40:05 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strchr_new(char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == '\n')
		return ((char *) &s[i]);
	return (NULL);
}

char	*ft_check_read(int fd, char *statik, char *buffer)
{
	ssize_t	read_bytes;
	char	*temp;

	read_bytes = 1;
	while (read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(statik);
			return (NULL);
		}
		if (read_bytes == 0)
			break ;
		buffer[read_bytes] = 0;
		if (!statik)
			statik = ft_strdup_get("");
		temp = statik;
		statik = ft_strjoin_get(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr_new(buffer))
			break ;
	}
	return (statik);
}

char	*ft_roll_and_print(char *line)
{
	char	*leftover;
	ssize_t	counter;

	counter = 0;
	while (line[counter] != '\n' && line[counter] != '\0')
		counter++;
	if (line[counter] == 0 || line[counter + 1] == 0)
		return (NULL);
	leftover = ft_substr_get(line, counter + 1, ft_strlen_get(line) - counter);
	if (*leftover == 0)
	{
		free(leftover);
		leftover = NULL;
	}
	line[counter + 1] = 0;
	return (leftover);
}

char	*get_next_line_bonus(int fd)
{
	static char	*statik[MAX_FD];
	char		*result;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(statik[fd]);
		statik[fd] = NULL;
		return (NULL);
	}
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	result = ft_check_read(fd, statik[fd], buffer);
	free(buffer);
	buffer = NULL;
	if (!result)
		return (NULL);
	statik[fd] = ft_roll_and_print(result);
	return (result);
}
