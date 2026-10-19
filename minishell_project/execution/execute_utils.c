/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 18:05:17 by hsbeh             #+#    #+#             */
/*   Updated: 2026/05/16 12:49:55 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_child_termination_signal(t_shell *shell, int return_status)
{
	int	signum;

	signum = WTERMSIG(return_status);
	shell->exit_status = 128 + signum;
	if (signum == SIGQUIT)
		ft_putendl_fd("Quit (core dumped)", 2);
	if (signum == SIGINT)
		ft_putchar_fd('\n', 1);
}

void	wait_child_processes(t_command *cmd, t_shell *shell)
{
	t_command	*temp;
	pid_t		pid;
	pid_t		the_last_pid;
	int			return_status;

	the_last_pid = -1;
	temp = cmd;
	while (temp != NULL)
	{
		the_last_pid = temp->pid;
		temp = temp->next;
	}
	while (1)
	{
		pid = waitpid(-1, &return_status, 0);
		if (pid == -1)
			break ;
		if (pid == the_last_pid)
		{
			if (WIFEXITED(return_status))
				shell->exit_status = WEXITSTATUS(return_status);
			else if (WIFSIGNALED(return_status))
				handle_child_termination_signal(shell, return_status);
		}
	}
}

int	print_dup2_error(void)
{
	perror("Dup2");
	return (-1);
}

int	is_there_path_in_env(char **env)
{
	int	i;

	i = 0;
	while (env != NULL && env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	get_exit_status_and_print(char *path, char **env)
{
	if (path == NULL && is_there_path_in_env(env) == 0)
		ft_putendl_fd(": No such file or directory", 2);
	else if (path == NULL)
		ft_putendl_fd(": command not found", 2);
	else if (check_is_a_directory(path) == 1)
	{
		ft_putendl_fd(": Is a directory", 2);
		return (126);
	}
	else if (errno == EACCES)
	{
		ft_putendl_fd(": Permission denied", 2);
		return (126);
	}
	else
		ft_putendl_fd(": No such file or directory", 2);
	return (127);
}
