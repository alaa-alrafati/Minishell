/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_controller.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 17:05:10 by hsbeh             #+#    #+#             */
/*   Updated: 2026/05/16 12:57:50 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	return_redirections_to_origion(t_shell *shell, t_command *cmd)
{
	if (cmd->output_fd > 1)
	{
		if (dup2(shell->stdout_origion, 1) == -1)
			return (print_dup2_error());
		close(cmd->output_fd);
	}
	if (cmd->input_fd > 0)
	{
		if (dup2(shell->stdin_origion, 0) == -1)
			return (print_dup2_error());
		close(cmd->input_fd);
	}
	return (0);
}

static void	pipe_controller(t_command *cmd)
{
	int	fd[2];

	if (cmd->next != NULL)
	{
		if (pipe(fd) == -1)
		{
			perror("Pipe");
			exit(1);
		}
		if (cmd->output_fd == 1)
			cmd->output_fd = fd[1];
		else
			close(fd[1]);
		if (cmd->next->input_fd == 0)
			cmd->next->input_fd = fd[0];
		else
			close(fd[0]);
	}
}

static void	run_the_cmd(t_shell *shell, t_command *cmd)
{
	if (cmd->next != NULL)
		pipe_controller(cmd);
	cmd->pid = simple_execution_cmd(shell, cmd);
	if (cmd->input_fd != 0)
		close(cmd->input_fd);
	if (cmd->output_fd != 1)
		close(cmd->output_fd);
}

static void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
}

void	execution_controller(t_shell *shell, t_command *cmd)
{
	t_command	*save_cmd_start;

	if (cmd == NULL)
		return ;
	ignore_signals();
	if (cmd->next == NULL)
	{
		if (cmd->args != NULL && cmd->args[0] != NULL
			&& is_cmd_built_in(cmd->args[0]) == 1)
		{
			if (setting_up_redirections(cmd, shell) == -1)
				return ;
			shell->exit_status = built_in_controller(cmd, shell);
			if (return_redirections_to_origion(shell, cmd) == -1)
				return ;
			return ;
		}
	}
	save_cmd_start = cmd;
	while (cmd != NULL)
	{
		run_the_cmd(shell, cmd);
		cmd = cmd->next;
	}
	wait_child_processes(save_cmd_start, shell);
}
