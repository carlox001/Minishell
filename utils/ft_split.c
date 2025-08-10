/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:52:22 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/24 10:38:54 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	ft_string_copy(char *dest, const char *source, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return ;
	while (source[i] != '\0' && i < size - 1)
	{
		dest[i] = source[i];
		i++;
	}
	dest[i] = '\0';
}

static char	**ft_free(char **matrix)
{
	char	**temp;

	temp = matrix;
	while (*temp != NULL)
	{
		free(*temp);
		temp++;
	}
	free(matrix);
	return (NULL);
}

static char	**ft_copy(const char *s, char c, char **matrix)
{
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i] && s[i] != '\0')
	{
		len = 0;
		while (s[i] == c && s[i] != '\0')
			i++;
		while (s[i] != c && s[i] != '\0')
		{
			len++;
			i++;
		}
		if (len > 0)
		{
			matrix[j] = (char *)malloc(sizeof(char) * (len + 1));
			if (!matrix[j])
				return (ft_free(matrix));
			ft_string_copy(matrix[j++], s + (i - len), len + 1);
		}
	}
	return (matrix);
}

static int	ft_count_words(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	while (s[i] != '\0')
	{
		count++;
		while (s[i] != c && s[i] != '\0')
			i++;
		while (s[i] == c && s[i] != '\0')
			i++;
	}
	return (count);
}

char	**ft_split(char *s, char c)
{
	char	**matrix;
	int		words_number;

	words_number = ft_count_words(s, c);
	matrix = (char **)malloc(sizeof(char *) * (words_number + 1));
	if (!matrix)
		return (NULL);
	matrix = ft_copy(s, c, matrix);
	if (matrix)
		matrix[words_number] = NULL;
	return (matrix);
}
