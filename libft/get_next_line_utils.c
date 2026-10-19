/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 15:35:42 by hsbeh             #+#    #+#             */
/*   Updated: 2026/04/23 15:35:42 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	len_of_read(char *string)
{
	size_t	x;

	if (string == NULL)
		return (0);
	x = 0;
	while (string[x] != '\0')
	{
		x++;
	}
	return (x);
}

void	add_buffer_to_saved(char *new_saved, char *buffer, char*saved)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	while (saved[x] != '\0')
	{
		new_saved[x] = saved[x];
		x++;
	}
	while (buffer[y] != '\0')
	{
		new_saved[x] = buffer[y];
		x++;
		y++;
	}
	new_saved[x] = '\0';
}

char	*update_saved(char *buffer, char*saved)
{
	size_t	len_of_buffer;
	size_t	len_of_saved;
	char	*new_saved;

	if (buffer == NULL)
		return (saved);
	if (saved == NULL)
	{
		saved = ft_calloc(1, sizeof(char));
		if (saved == NULL)
			return (NULL);
		saved[0] = '\0';
	}
	len_of_buffer = len_of_read(buffer);
	len_of_saved = len_of_read(saved);
	new_saved = ft_calloc(len_of_buffer + len_of_saved + 1, sizeof(char));
	if (new_saved == NULL)
	{
		free(saved);
		return (NULL);
	}
	add_buffer_to_saved(new_saved, buffer, saved);
	free(saved);
	return (new_saved);
}

char	*get_first_line(char *saved)
{
	char	*line;
	size_t	len;
	size_t	i;

	if (saved == NULL)
		return (NULL);
	len = 0;
	while (saved[len] != '\n' && saved[len] != '\0')
		len++;
	if (saved[len] == '\n')
		len++;
	line = ft_calloc((len + 1), sizeof(char));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = saved[i];
		i++;
	}
	return (line);
}
