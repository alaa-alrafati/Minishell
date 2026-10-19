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

static	int	handle_quotations(char *rl, int *x, int *quote)
{
	char	q;

	if (rl[*x] == '\'')
		*quote = 1;
	else if (rl[*x] == '\"')
		*quote = 2;
	q = rl[*x];
	(*x)++;
	while (rl[*x] != '\0' && rl[*x] != q)
		(*x)++;
	if (rl[*x] == '\0')
	{
		ft_putstr_fd("Syntax Error: quote unclosed\n", 2);
		return (-1);
	}
	(*x)++;
	return (0);
}

static	void	save_words(char *word, int *quote, t_shell *shell)
{
	t_lexer	*new;

	new = make_new_node(word, WORD);
	if (new != NULL)
		new->quote_type = *quote;
	free(word);
	add_token(&(shell->tokens), new);
}

int	handle_words(char *rl, int x, t_shell *shell)
{
	char	*word;
	int		start;
	int		quote;

	start = x;
	quote = 0;
	while (rl[x] != '\0' && !((rl[x] >= 9 && rl[x] <= 13) || (rl[x] == 32))
		&& rl[x] != '|' && rl[x] != '<' && rl[x] != '>')
	{
		if (rl[x] == '\'' || rl[x] == '\"')
		{
			if (handle_quotations(rl, &x, &quote) == -1)
				return (-1);
		}
		else
			x++;
	}
	word = ft_substr(rl, start, x - start);
	if (!word)
		return (x);
	save_words(word, &quote, shell);
	return (x);
}

int	handle_special_redir_in(char *rl, int x, t_shell *shell)
{
	t_lexer	*new;

	if (rl[x + 1] == '<')
	{
		new = make_new_node("<<", HERE_DOC);
		add_token(&(shell->tokens), new);
		x += 2;
	}
	else
	{
		new = make_new_node("<", REDIR_IN);
		add_token(&(shell->tokens), new);
		x++;
	}
	return (x);
}
