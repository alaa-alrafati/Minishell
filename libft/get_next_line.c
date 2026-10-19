/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 15:35:47 by hsbeh             #+#    #+#             */
/*   Updated: 2026/04/23 15:35:47 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*free_saved_return_null(char *saved)
{
	free(saved);
	return (NULL);
}

char	*remove_line(char *saved)
{
	size_t	len;
	size_t	x;
	char	*remaining_saved;

	if (saved == NULL)
		return (NULL);
	len = 0;
	while (saved[len] != '\n' && saved[len] != '\0')
		len++;
	if (saved[len] == '\0')
		return (free_saved_return_null(saved));
	remaining_saved = ft_calloc((len_of_read(saved) - len), sizeof(char));
	if (!remaining_saved)
		return (free_saved_return_null(saved));
	len++;
	x = 0;
	while (saved[len] != '\0')
		remaining_saved[x++] = saved[len++];
	free(saved);
	return (remaining_saved);
}

size_t	contains_newline(char *saved)
{
	size_t	index;

	index = 0;
	if (saved == NULL)
		return (0);
	while (saved[index] != '\0')
	{
		if (saved[index] == '\n')
			return (1);
		index++;
	}
	return (0);
}

char	*read_line(int fd, char *saved)
{
	ssize_t			num_of_bytes_read;
	char			*what_been_read;

	what_been_read = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (what_been_read == NULL)
		return (free_saved_return_null(saved));
	num_of_bytes_read = 1;
	while (!contains_newline(saved) && num_of_bytes_read != 0)
	{
		num_of_bytes_read = read(fd, what_been_read, BUFFER_SIZE);
		if (num_of_bytes_read == -1)
		{
			free(what_been_read);
			return (free_saved_return_null(saved));
		}
		what_been_read[num_of_bytes_read] = '\0';
		saved = update_saved(what_been_read, saved);
		if (saved == NULL)
		{
			free(what_been_read);
			return (NULL);
		}
	}
	free(what_been_read);
	return (saved);
}

char	*get_next_line(int fd)
{
	static char		*saved;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	saved = read_line(fd, saved);
	if (saved == NULL)
		return (NULL);
	if (*saved == '\0')
	{
		free(saved);
		saved = NULL;
		return (NULL);
	}
	line = get_first_line(saved);
	if (line == NULL)
	{
		free(saved);
		saved = NULL;
		return (NULL);
	}
	saved = remove_line(saved);
	return (line);
}
