/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 20:48:40 by hsbeh             #+#    #+#             */
/*   Updated: 2026/05/16 13:23:09 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setting_up_child_redirections(t_command *cmd, t_shell *shell)
{
	close_original_fds(shell);
	if (cmd->input_fd > 0)
	{
		if (dup2(cmd->input_fd, 0) == -1)
		{
			close(cmd->input_fd);
			if (cmd->output_fd > 1)
				close(cmd->output_fd);
			perror("Dup2");
			exit(1);
		}
		close(cmd->input_fd);
		cmd->input_fd = -1;
	}
	if (cmd->output_fd > 1)
	{
		if (dup2(cmd->output_fd, 1) == -1)
		{
			close(cmd->output_fd);
			perror("Dup2");
			exit(1);
		}
		close(cmd->output_fd);
		cmd->output_fd = -1;
	}
}

int	check_is_a_directory(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode))
			return (1);
	}
	return (0);
}

static void	print_error_exit(t_shell *shell, char *cmd, char **env, char *path)
{
	int	exit_num;

	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	exit_num = get_exit_status_and_print(path, env);
	if (path != NULL)
		free(path);
	free_args(env);
	clean_up_our_minishell(shell);
	exit(exit_num);
}

static void	execute_non_built_in_cmd(t_command *cmd, t_shell *shell)
{
	char	**our_envp;
	char	*cmd_path;

	our_envp = convert_env_to_array(shell->env_list);
	if (our_envp == NULL)
	{
		perror("Malloc");
		exit(1);
	}
	if (cmd->args[0][0] == '\0')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putendl_fd(": command not found", 2);
		free_args(our_envp);
		clean_up_our_minishell(shell);
		exit(127);
	}
	cmd_path = check_cmd_path(cmd->args[0], our_envp);
	if (cmd_path != NULL)
		execve(cmd_path, cmd->args, our_envp);
	print_error_exit(shell, cmd->args[0], our_envp, cmd_path);
}

pid_t	simple_execution_cmd(t_shell *shell, t_command *cmd)
{
	pid_t		my_fork;

	my_fork = fork();
	if (handle_fork_error(my_fork, shell) == -1)
		return (-1);
	if (my_fork == 0)
	{
		restore_default_signals();
		setting_up_child_redirections(cmd, shell);
		close_all_fds(shell);
		if (cmd->args == NULL || cmd->args[0] == NULL)
		{
			clean_up_our_minishell(shell);
			exit(0);
		}
		if (is_cmd_built_in(cmd->args[0]) == 1)
		{
			shell->exit_status = built_in_controller(cmd, shell);
			clean_up_our_minishell(shell);
			exit(shell->exit_status);
		}
		execute_non_built_in_cmd(cmd, shell);
	}
	return (my_fork);
}
