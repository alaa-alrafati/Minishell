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

static	int	handle_redirection2(int type, char *name_of_file,
	t_command *cmd, t_shell *shell)
{
	if (type == REDIR_IN)
	{
		if (cmd->input_fd != 0)
			close(cmd->input_fd);
		cmd->input_fd = open(name_of_file, O_RDONLY);
	}
	else if (type == HERE_DOC)
	{
		if (handle_here_doc(name_of_file, cmd, shell) == -1)
			return (-1);
	}
	return (0);
}

static	int	handle_redirection(t_command *cmd,
	t_lexer **current, t_shell *shell)
{
	char	*name_of_file;
	int		type;

	type = (*current)->type;
	(*current) = (*current)->next;
	if (*current == NULL)
	{
		ft_putstr_fd("-Minishell: syntax error ", 2);
		ft_putendl_fd("near unexpected token `newline'", 2);
		shell->exit_status = 2;
		return (-1);
	}
	if ((*current)->type != WORD)
	{
		syntax_error(current, shell);
		return (-1);
	}
	name_of_file = (*current)->value;
	if (handle_redirection2(type, name_of_file, cmd, shell) == -1)
		return (-1);
	if (handle_redir3(type, name_of_file, cmd, shell) == -1)
		return (-1);
	(*current) = (*current)->next;
	return (0);
}

static	int	fill(int *x, t_command *cmd, t_lexer **current, t_shell *shell)
{
	if ((*current)->type == WORD)
	{
		cmd->args[*x] = ft_strdup((*current)->value);
		if (!cmd->args[*x])
			return (-1);
		(*x)++;
		(*current) = (*current)->next;
	}
	else if ((*current)->type == REDIR_IN || (*current)->type == REDIR_OUT
		|| (*current)->type == HERE_DOC || (*current)->type == APPEND)
	{
		if (handle_redirection(cmd, current, shell) == -1)
			return (-1);
	}
	else
		(*current) = (*current)->next;
	return (0);
}

static	int	count_words(t_lexer *current)
{
	int	count;

	count = 0;
	while (current != NULL && current->type != PIPE)
	{
		if (current->type == WORD)
		{
			count++;
			current = current->next;
		}
		else if (current->type == REDIR_IN || current->type == REDIR_OUT
			|| current->type == HERE_DOC || current->type == APPEND)
		{
			current = current->next;
			if (current != NULL)
				current = current->next;
		}
	}
	return (count);
}

//command char **args //lexer char *value
int	fill_cmd_struct_data(t_command *cmd, t_lexer **current, t_shell *shell)
{
	int	x;
	int	words_num;

	words_num = count_words(*current);
	cmd->args = ft_calloc((words_num + 1), sizeof (char *));
	if (!cmd->args)
		return (-1);
	x = 0;
	while (*current != NULL && (*current)->type != PIPE)
	{
		if (fill(&x, cmd, current, shell) == -1)
			return (-1);
	}
	cmd->args[x] = NULL;
	return (0);
}
