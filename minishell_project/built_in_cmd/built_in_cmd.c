/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:34:16 by hsbeh             #+#    #+#             */
/*   Updated: 2026/05/16 12:44:31 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_cmd(t_envir *env, char **arg)
{
	if (arg[1] != NULL)
	{
		ft_putendl_fd("env: too many arguments", 2);
		return (1);
	}
	while (env != NULL)
	{
		if (env->value != NULL)
		{
			ft_putstr_fd(env->key, 1);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(env->value, 1);
		}
		env = env->next;
	}
	return (0);
}

int	pwd_cmd(void)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, sizeof(pwd)) != NULL)
	{
		ft_putendl_fd(pwd, 1);
		return (0);
	}
	else
		perror("minishell: pwd");
	return (1);
}

void	print_for_echo_arg(char **arg, int start_print, int is_there_n_flag)
{
	while (arg[start_print] != NULL)
	{
		ft_putstr_fd(arg[start_print], 1);
		if (arg[start_print + 1] != NULL)
			ft_putchar_fd(' ', 1);
		start_print++;
	}
	if (is_there_n_flag == 0)
		ft_putchar_fd('\n', 1);
}

int	check_flag(char **array_of_arg)
{
	int	arg;
	int	i;

	arg = 1;
	while (array_of_arg[arg] != NULL)
	{
		i = 0;
		if (array_of_arg[arg][i] == '-' && array_of_arg[arg][i + 1] == 'n')
		{
			i = 1;
			while (array_of_arg[arg][i] == 'n')
				i++;
			if (array_of_arg[arg][i] != '\0')
				break ;
		}
		else
			break ;
		arg++;
	}
	return (arg);
}

int	echo_cmd(char **array_of_arg)
{
	int	start_print;
	int	is_there_n_flag;

	start_print = check_flag(array_of_arg);
	if (start_print >= 2)
		is_there_n_flag = 1;
	else
		is_there_n_flag = 0;
	print_for_echo_arg(array_of_arg, start_print, is_there_n_flag);
	return (0);
}
