/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 23:28:44 by hsbeh             #+#    #+#             */
/*   Updated: 2026/05/16 13:15:18 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_value_key_return_one(char *env_value, char *env_key)
{
	free(env_value);
	free(env_key);
	return (1);
}

void	free_env(t_envir *the_start_node)
{
	t_envir	*temp;

	while (the_start_node != NULL)
	{
		temp = the_start_node->next;
		if (the_start_node->key != NULL)
			free(the_start_node->key);
		if (the_start_node->value != NULL)
			free(the_start_node->value);
		free(the_start_node);
		the_start_node = temp;
	}
}

void	close_original_fds(t_shell *shell)
{
	close(shell->stdin_origion);
	shell->stdin_origion = -1;
	close(shell->stdout_origion);
	shell->stdout_origion = -1;
}

void	restore_default_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
}

void	close_all_fds(t_shell *shell)
{
	t_command	*temp_cmd;

	temp_cmd = shell->commands;
	while (temp_cmd != NULL)
	{
		if (temp_cmd->input_fd > 0)
			close(temp_cmd->input_fd);
		if (temp_cmd->output_fd > 1)
			close(temp_cmd->output_fd);
		temp_cmd = temp_cmd->next;
	}
}
