/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:01:43 by aalrofat          #+#    #+#             */
/*   Updated: 2026/05/08 16:48:52 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	clean_up_our_minishell(t_shell *shell)
{
	int	exit_status;

	if (shell == NULL)
		return (0);
	exit_status = shell->exit_status;
	if (shell->env_list)
		free_env(shell->env_list);
	if (shell->tokens)
		free_lexer(&(shell->tokens));
	if (shell->commands)
		free_commands(&(shell->commands));
	if (shell->stdin_origion > 2)
		close(shell->stdin_origion);
	if (shell->stdout_origion > 2)
		close(shell->stdout_origion);
	rl_clear_history();
	return (exit_status);
}

int	lex_expand_and_parse(char *rl, t_shell *shell)
{
	if (start_lexing(rl, shell) == -1)
	{
		free(rl);
		return (-1);
	}
	start_expand(shell);
	if (start_parsing(shell) == -1)
	{
		free_lexer(&(shell->tokens));
		free_commands(&(shell->commands));
		free(rl);
		return (-1);
	}
	execution_controller(shell, shell->commands);
	free_lexer(&(shell->tokens));
	free_commands(&(shell->commands));
	shell->tokens = NULL;
	shell->commands = NULL;
	free(rl);
	shell->tokens = NULL;
	return (0);
}
