/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_controller.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 16:56:29 by hsbeh             #+#    #+#             */
/*   Updated: 2026/05/15 14:49:19 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_in_controller(t_command *cmd, t_shell *shell)
{
	int	exit_status;

	if (cmd == NULL || cmd->args == NULL || cmd->args[0] == NULL)
		return (-1);
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		exit_status = cd_cmd(&(shell->env_list), cmd->args);
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		exit_status = pwd_cmd();
	else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		exit_status = echo_cmd(cmd->args);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		exit_status = export_cmd(cmd->args, &(shell->env_list));
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		exit_status = env_cmd(shell->env_list, cmd->args);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		exit_status = unset_cmd(&(shell->env_list), cmd->args);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
	{
		exit_cmd(cmd->args, shell);
		exit_status = shell->exit_status;
	}
	else
		return (-1);
	return (exit_status);
}

int	is_cmd_built_in(char *cmd)
{
	if (cmd == NULL)
		return (0);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}
