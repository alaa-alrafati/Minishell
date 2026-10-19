/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 00:54:52 by hsbeh             #+#    #+#             */
/*   Updated: 2026/05/16 13:23:23 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	setup_input_redirect(t_command *cmd)
{
	if (cmd->input_fd > 0)
	{
		if (dup2(cmd->input_fd, 0) == -1)
		{
			close(cmd->input_fd);
			if (cmd->output_fd > 1)
				close(cmd->output_fd);
			return (print_dup2_error());
		}
	}
	return (0);
}

static int	setup_output_redirect(t_command *cmd, t_shell *shell)
{
	if (cmd->output_fd > 1)
	{
		if (dup2(cmd->output_fd, 1) == -1)
		{
			if (cmd->input_fd > 0)
			{
				close(cmd->input_fd);
				if (dup2(shell->stdin_origion, 0) == -1)
				{
					close(cmd->output_fd);
					return (print_dup2_error());
				}
			}
			close(cmd->output_fd);
			return (print_dup2_error());
		}
	}
	return (0);
}

int	setting_up_redirections(t_command *cmd, t_shell *shell)
{
	if (setup_input_redirect(cmd) == -1)
		return (-1);
	if (setup_output_redirect(cmd, shell) == -1)
		return (-1);
	return (0);
}

int	handle_fork_error(pid_t pid, t_shell *shell)
{
	if (pid == -1)
	{
		perror("minishell: fork");
		shell->exit_status = 1;
		return (-1);
	}
	return (0);
}
