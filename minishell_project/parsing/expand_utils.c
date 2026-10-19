/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalrofat <aalrofat@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:01:43 by aalrofat          #+#    #+#             */
/*   Updated: 2026/04/22 18:05:59 by aalrofat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_for_expand(char *temp, char *val, char	*key)
{
	free(temp);
	free(val);
	free(key);
}

char	*find_key(int *x, char *value)
{
	char	*key;
	int		start;

	(*x)++;
	start = *x;
	if (ft_isdigit(value[*x]) || value[*x] == '?')
		(*x)++;
	else
	{
		while (value[*x] != '\0' && (ft_isalnum(value[*x]) || value[*x] == '_'))
			(*x)++;
	}
	key = ft_substr(value, start, *x - start);
	return (key);
}

int	check_quotations_and_update(int *quote, char x)
{
	if ((x == '\'' || x == '\"') && *quote == 0)
	{
		if (x == '\'')
			*quote = 1;
		else
			*quote = 2;
		return (1);
	}
	else if ((x == '\'' && *quote == 1) || (x == '\"' && *quote == 2))
	{
		*quote = 0;
		return (1);
	}
	return (0);
}

char	*remove_quote(char *value)
{
	char	*str;
	int		quote;
	int		x;
	int		y;

	quote = 0;
	x = 0;
	y = 0;
	str = malloc(ft_strlen(value) + 1);
	if (!str)
	{
		free(value);
		return (NULL);
	}
	while (value[x] != '\0')
	{
		if (check_quotations_and_update(&quote, value[x]) != 0)
			x++;
		else
			str[y++] = value[x++];
	}
	str[y] = '\0';
	free(value);
	return (str);
}
