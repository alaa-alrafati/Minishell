/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 21:42:28 by hsbeh             #+#    #+#             */
/*   Updated: 2026/05/16 12:40:15 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_envir **env_array, int env_list_count)
{
	int	i;

	i = 0;
	while (i < env_list_count)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env_array[i]->key, 1);
		if (env_array[i]->value != NULL)
		{
			ft_putchar_fd('=', 1);
			ft_putchar_fd('"', 1);
			ft_putstr_fd(env_array[i]->value, 1);
			ft_putchar_fd('"', 1);
		}
		ft_putstr_fd("\n", 1);
		i++;
	}
}

int	handle_cd_without_args(t_envir **env, char *old_path)
{
	char	*home_path_value;

	home_path_value = get_key_value_from_env(*env, "HOME");
	if (home_path_value == NULL)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		return (1);
	}
	if (chdir(home_path_value) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(home_path_value);
		return (1);
	}
	read_new_path_and_update_old_path(env, old_path);
	return (0);
}

void	handle_exit_error(char *array_of_arg, t_shell *shell)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(array_of_arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	clean_up_our_minishell(shell);
	exit(2);
}

int	check_digits_and_skip_spaces(char *arg, int i)
{
	while (arg[i] != '\0')
	{
		if (arg[i] == 32 || (arg[i] >= 9 && arg[i] <= 13))
		{
			while (arg[i] == 32 || (arg[i] >= 9 && arg[i] <= 13))
				i++;
			if (arg[i] != '\0')
				return (0);
			break ;
		}
		if (ft_isdigit(arg[i]) != 1)
			return (0);
		i++;
	}
	return (1);
}
