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

static	int	count_pipes(t_lexer *current)
{
	int	count;

	count = 0;
	while (current != NULL && current->type == PIPE)
	{
		count++;
		current = current->next;
	}
	return (count);
}

static	int	handle_pipe_at_the_end(t_lexer *current, t_shell *shell)
{
	int	count_pipe;

	count_pipe = count_pipes(current);
	if (count_pipe > 1)
	{
		if (count_pipe == 2 || count_pipe == 3)
			ft_putendl_fd("-Minishell: syntax error near unexpected token `|'",
				2);
		else if (count_pipe >= 4)
		{
			ft_putstr_fd("-Minishell: syntax error ", 2);
			ft_putendl_fd("near unexpected token `||'", 2);
		}
		shell->exit_status = 2;
		return (-1);
	}
	else if (count_pipe == 1 && current->next == NULL)
	{
		ft_putstr_fd("-Minishell: syntax error near unexpected token `|'\n", 2);
		shell->exit_status = 2;
		return (-1);
	}
	return (0);
}

static	t_command	*init_cmd_and_create_node(void)
{
	t_command	*node;

	node = malloc(sizeof(t_command));
	if (!node)
		return (NULL);
	node->args = NULL;
	node->input_fd = 0;
	node->output_fd = 1;
	node->exit_num = 0;
	node->pid = -1;
	node->next = NULL;
	return (node);
}

static	int	handle_pipe_at_the_start(t_lexer *current, t_shell *shell)
{
	if (current->next != NULL && current->next->type == PIPE)
		ft_putstr_fd("-Minishell: syntax error near unexpected token `||'\n",
			2);
	else
		ft_putstr_fd("-Minishell: syntax error near unexpected token `|'\n", 2);
	shell->exit_status = 2;
	return (-1);
}

int	start_parsing(t_shell *shell)
{
	t_lexer		*current;
	t_command	*cmd;

	current = shell->tokens;
	if (current == NULL)
		return (0);
	if (current->type == PIPE)
		return (handle_pipe_at_the_start(current, shell));
	while (current != NULL)
	{
		cmd = init_cmd_and_create_node();
		if (!cmd)
			return (-1);
		connect_cmd_to_commands_shell(cmd, shell);
		if (fill_cmd_struct_data(cmd, &current, shell) == -1)
			return (-1);
		if (current != NULL && current->type == PIPE)
		{
			if (handle_pipe_at_the_end(current, shell) == -1)
				return (-1);
			current = current->next;
		}
	}
	return (0);
}
