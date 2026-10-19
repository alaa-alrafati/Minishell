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

void	free_args(char **args)
{
	int	x;

	x = 0;
	if (!args)
		return ;
	while (args[x] != NULL)
	{
		free(args[x]);
		x++;
	}
	free(args);
}

void	free_commands(t_command **commands)
{
	t_command	*current;
	t_command	*next_node;

	if (!commands || !*commands)
		return ;
	current = *commands;
	while (current != NULL)
	{
		next_node = current->next;
		if (current->args)
			free_args(current->args);
		if (current->input_fd > 0)
			close(current->input_fd);
		if (current->output_fd > 1)
			close(current->output_fd);
		free(current);
		current = next_node;
	}
	*commands = NULL;
}

void	free_lexer(t_lexer **tokens)
{
	t_lexer	*current;
	t_lexer	*next_node;

	if (!tokens || !*tokens)
		return ;
	current = *tokens;
	while (current != NULL)
	{
		next_node = current->next;
		free(current->value);
		free(current);
		current = next_node;
	}
	*tokens = NULL;
}
