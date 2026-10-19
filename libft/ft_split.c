/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 15:30:37 by hsbeh             #+#    #+#             */
/*   Updated: 2026/04/23 15:30:38 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_word(char const *s, char delimiter)
{
	size_t	words;

	words = 0;
	while (*s)
	{
		while (*s && *s == delimiter)
			s++;
		if (*s && *s != delimiter)
		{
			words++;
			while (*s && *s != delimiter)
				s++;
		}
	}
	return (words);
}

static char	*allocat_word(const char *s, char delimiter)
{
	size_t	len;
	size_t	i;
	char	*word;

	len = 0;
	while (s[len] && s[len] != delimiter)
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

static void	free_split_words(char **split_words)
{
	size_t	i;

	i = 0;
	while (split_words && split_words[i])
		free(split_words[i++]);
	free(split_words);
}

static char	**my_splitter(char const *s, char delimiter, char **split_words)
{
	size_t	words;

	words = 0;
	while (*s != '\0')
	{
		while (*s != '\0' && *s == delimiter)
			s++;
		if (*s && *s != delimiter)
		{
			split_words[words] = allocat_word(s, delimiter);
			if (split_words[words] == NULL)
			{
				free_split_words(split_words);
				return (NULL);
			}
			words++;
			while (*s != '\0' && *s != delimiter)
				s++;
		}
	}
	split_words[words] = NULL;
	return (split_words);
}

char	**ft_split(char const *s, char c)
{
	size_t	words;
	char	**split_words;

	if (s == NULL)
		return (NULL);
	words = count_word(s, c);
	split_words = (char **)malloc((words + 1) * sizeof(char *));
	if (split_words == NULL)
		return (NULL);
	return (my_splitter(s, c, split_words));
}
