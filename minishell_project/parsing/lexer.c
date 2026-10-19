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

static	int	handle_special_redir_out(char *rl, int x, t_shell *shell)
{
	t_lexer	*new;

	if (rl[x + 1] == '>')
	{
		new = make_new_node(">>", APPEND);
		add_token(&(shell->tokens), new);
		x += 2;
	}
	else
	{
		new = make_new_node(">", REDIR_OUT);
		add_token(&(shell->tokens), new);
		x++;
	}
	return (x);
}

void	add_token(t_lexer **tokens, t_lexer *new_node)
{
	t_lexer	*temp;

	if (new_node == NULL)
		return ;
	if (*tokens == NULL)
	{
		*tokens = new_node;
		return ;
	}
	temp = *tokens;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

t_lexer	*make_new_node(char *str, t_type type)
{
	t_lexer	*new_node;

	new_node = malloc(sizeof(t_lexer));
	if (!new_node)
		return (NULL);
	new_node->value = ft_strdup(str);
	if (!new_node->value)
	{
		free(new_node);
		return (NULL);
	}
	new_node->type = type;
	new_node->quote_type = 0;
	new_node->next = NULL;
	return (new_node);
}

static	int	handle_special(char *rl, int x, t_shell *shell)
{
	t_lexer	*new;

	if (rl[x] == '|')
	{
		new = make_new_node("|", PIPE);
		add_token(&(shell->tokens), new);
		x++;
	}
	else if (rl[x] == '<')
		x = handle_special_redir_in(rl, x, shell);
	else if (rl[x] == '>')
		x = handle_special_redir_out(rl, x, shell);
	return (x);
}

int	start_lexing(char *rl, t_shell *shell)
{
	int		x;

	x = 0;
	while (rl[x] != '\0')
	{
		while ((rl[x] >= 9 && rl[x] <= 13) || (rl[x] == 32))
			x++;
		if (rl[x] == '\0')
			return (0);
		if (rl[x] == '|' || rl[x] == '<' || rl[x] == '>')
			x = handle_special(rl, x, shell);
		else
		{
			x = handle_words(rl, x, shell);
			if (x == -1)
			{
				free_lexer(&(shell->tokens));
				return (-1);
			}
		}
	}
	return (0);
}
