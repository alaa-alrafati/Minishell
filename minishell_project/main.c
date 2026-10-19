/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:01:43 by aalrofat          #+#    #+#             */
/*   Updated: 2026/05/16 13:37:25 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

static	void	handler_signint_for_minishell(int signum)
{
	(void)signum;
	g_signal = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static	void	init_shell(char **envp, t_shell *shell)
{
	shell->env_list = fill_envir_struct(envp);
	shell->tokens = NULL;
	shell->commands = NULL;
	shell->envp = envp;
	shell->exit_status = 0;
	shell->stdout_origion = dup(1);
	shell->stdin_origion = dup(0);
}

static	char	*main_readline(t_shell *shell)
{
	char	*rl;

	g_signal = 0;
	rl = readline("Our_Minishell$ ");
	if (rl == NULL)
	{
		printf("exit\n");
		return (NULL);
	}
	if (g_signal == 130)
	{
		shell->exit_status = 130;
	}
	if (rl[0] != '\0')
		add_history(rl);
	return (rl);
}

static	int	init_main(int argc, char **argv, char **envp, t_shell *shell)
{
	if (argc != 1 || argv[1] != NULL)
	{
		ft_putstr_fd("Syntax Error: Minishell doesn't accept arguments\n", 2);
		return (1);
	}
	init_shell(envp, shell);
	g_signal = 0;
	signal(SIGINT, handler_signint_for_minishell);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*rl;

	if (init_main(argc, argv, envp, &shell) != 0)
		return (1);
	while (1)
	{
		signal(SIGINT, handler_signint_for_minishell);
		signal(SIGQUIT, SIG_IGN);
		g_signal = 0;
		rl = main_readline(&shell);
		if (rl == NULL)
			break ;
		if (rl[0] == '\0')
		{
			free(rl);
			continue ;
		}
		if (lex_expand_and_parse(rl, &shell) == -1)
			continue ;
	}
	return (clean_up_our_minishell(&shell));
}
