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

void	syntax_error(t_lexer **current, t_shell *shell)
{
	ft_putstr_fd("-Minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd((*current)->value, 2);
	ft_putstr_fd("'\n", 2);
	shell->exit_status = 2;
}

void	connect_cmd_to_commands_shell(t_command *cmd, t_shell *shell)
{
	t_command	*temp;

	if (shell->commands == NULL)
	{
		shell->commands = cmd;
		return ;
	}
	temp = shell->commands;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = cmd;
}

int	handle_redir3(int type, char *name_of_file,
	t_command *cmd, t_shell *shell)
{
	if (type == REDIR_OUT)
	{
		if (cmd->output_fd != 1)
			close(cmd->output_fd);
		cmd->output_fd = open(name_of_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (type == APPEND)
	{
		if (cmd->output_fd != 1)
			close(cmd->output_fd);
		cmd->output_fd = open(name_of_file,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (cmd->input_fd == -1 || cmd->output_fd == -1)
	{
		ft_putstr_fd("-Minishell: ", 2);
		perror(name_of_file);
		shell->exit_status = 1;
		return (-1);
	}
	return (0);
}
