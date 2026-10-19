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

static	void	handler_signint_for_heredoc(int signum)
{
	(void)signum;
	g_signal = 130;
	printf("\n");
	close(0);
}

static	int	readline_in_here_doc(char **line, char *delimiter, t_shell *shell)
{
	*line = readline("> ");
	if (!*line || g_signal == 130)
	{
		if (g_signal == 130)
		{
			free(*line);
			shell->exit_status = 130;
		}
		else
		{
			ft_putstr_fd("-Minishell: warning: here-document ", 2);
			ft_putstr_fd("delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(delimiter, 2);
			ft_putstr_fd("')\n", 2);
			shell->exit_status = 0;
		}
		return (1);
	}
	if (ft_strncmp(*line, delimiter, ft_strlen(delimiter)) == 0
		&& ft_strlen(*line) == ft_strlen(delimiter))
	{
		free(*line);
		return (1);
	}
	return (0);
}

static	int	open_tempfile(t_shell *shell)
{
	int	fd;

	fd = open(".temp_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("-Minishell: heredoc: ", 2);
		perror(".temp_file");
		shell->exit_status = 1;
		return (-1);
	}
	return (fd);
}

static int	init_signal_here_doc(t_shell *shell)
{
	int	fd;

	g_signal = 0;
	signal(SIGINT, handler_signint_for_heredoc);
	signal(SIGQUIT, SIG_IGN);
	fd = open_tempfile(shell);
	return (fd);
}

int	handle_here_doc(char *delimiter, t_command *cmd, t_shell *shell)
{
	int		fd;
	char	*line;

	fd = init_signal_here_doc(shell);
	if (fd == -1)
		return (-1);
	while (1)
	{
		if (readline_in_here_doc(&line, delimiter, shell) == 1)
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	dup2(shell->stdin_origion, 0);
	if (g_signal == 130)
	{
		unlink(".temp_file");
		return (-1);
	}
	if (cmd->input_fd != 0)
		close(cmd->input_fd);
	cmd->input_fd = open(".temp_file", O_RDONLY);
	unlink(".temp_file");
	return (0);
}
