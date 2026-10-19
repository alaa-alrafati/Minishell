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

static	char	*the_collect(char *str, int x, char *value)
{
	char	*str_cpy;
	char	*temp;

	str_cpy = ft_substr(value, x, 1);
	temp = str;
	str = ft_strjoin(str, str_cpy);
	free(temp);
	free(str_cpy);
	return (str);
}

static char	*get_the_value(char *key, t_shell *shell)
{
	t_envir	*current;

	if (key[0] == '?' && key[1] == '\0')
		return (ft_itoa(shell->exit_status));
	current = shell->env_list;
	while (current != NULL)
	{
		if (ft_strncmp(key, current->key, ft_strlen(key)) == 0
			&& ft_strlen(key) == ft_strlen(current->key))
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (ft_strdup(""));
}

static	char	*handle_dollar_sign(char *str, int *x,
	char *value, t_shell *shell)
{
	char	*key;
	char	*val;
	char	*temp;

	key = find_key(x, value);
	val = get_the_value(key, shell);
	if (!val)
	{
		val = ft_strdup("");
		if (val == NULL)
		{
			free(str);
			free(key);
			return (NULL);
		}
	}
	temp = str;
	str = ft_strjoin(str, val);
	if (str == NULL)
	{
		free_for_expand(temp, val, key);
		return (NULL);
	}
	free_for_expand(temp, val, key);
	return (str);
}

static	char	*expand_action(char *value, t_shell *shell)
{
	char	*str;
	int		quote;
	int		x;

	str = ft_calloc(1, sizeof(char));
	if (!str)
	{
		free(value);
		return (NULL);
	}
	x = 0;
	quote = 0;
	while (value[x] != '\0')
	{
		check_quotations_and_update(&quote, value[x]);
		if (value[x] == '$' && value[x + 1] != '\0' && quote != 1
			&& (ft_isalnum(value[x + 1])
				|| value[x + 1] == '_' || value[x + 1] == '?'))
			str = handle_dollar_sign(str, &x, value, shell);
		else
			str = the_collect(str, x++, value);
	}
	free(value);
	return (str);
}

void	start_expand(t_shell *shell)
{
	t_lexer	*current;

	current = shell->tokens;
	while (current != NULL)
	{
		if (current->type == WORD)
		{
			current->value = expand_action(current->value, shell);
			if (current->value == NULL)
				return ;
		}
		if (current->quote_type != 0 && current->value != NULL)
			current->value = remove_quote(current->value);
		current = current->next;
	}
}
