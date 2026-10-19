/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 12:04:08 by hsbeh             #+#    #+#             */
/*   Updated: 2026/05/16 12:47:07 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	compare_str_with_long_long_limits(char *str, int sign, int len)
{
	if (sign == 1)
	{
		if (ft_strncmp(str, STR_LONG_LONG_MAX, len) > 0)
			return (1);
	}
	else if (sign == -1)
	{
		if (ft_strncmp(str, STR_LONG_LONG_MIN, len) > 0)
			return (1);
	}
	return (0);
}

static int	check_long_long_limits(char *str)
{
	int	len;
	int	sign;
	int	i;

	i = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] == '0')
		i++;
	len = 0;
	while (str[len + i] >= '0' && str[len + i] <= '9')
		len++;
	if (len > 19)
		return (1);
	else if (len == 19)
		if (compare_str_with_long_long_limits(str + i, sign, len) == 1)
			return (1);
	return (0);
}

static int	check_is_num_and_limit(char *arg)
{
	int	i;

	if (arg == NULL || arg[0] == '\0')
		return (0);
	i = 0;
	while (arg[i] == 32 || (arg[i] >= 9 && arg[i] <= 13))
		i++;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (ft_isdigit(arg[i]) != 1)
		return (0);
	if (check_digits_and_skip_spaces(arg, i) == 0)
		return (0);
	if (check_long_long_limits(arg) == 1)
		return (0);
	return (1);
}

static long long	ft_atoi_for_exit_cmd(const char *str)
{
	unsigned long long	result;
	int					i;
	int					sign;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	if (sign == -1)
		return (-(result));
	return (result);
}

void	exit_cmd(char **array_of_arg, t_shell *shell)
{
	long long	exit_status;

	if (shell->commands != NULL && shell->commands->next == NULL)
		ft_putendl_fd("exit", 2);
	if (array_of_arg[1] == NULL)
	{
		clean_up_our_minishell(shell);
		exit(shell->exit_status);
	}
	if (check_is_num_and_limit(array_of_arg[1]) == 0)
		handle_exit_error(array_of_arg[1], shell);
	if (array_of_arg[2] != NULL)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		shell->exit_status = 1;
		return ;
	}
	exit_status = ft_atoi_for_exit_cmd(array_of_arg[1]);
	exit_status = (exit_status % 256 + 256) % 256;
	clean_up_our_minishell(shell);
	exit(exit_status);
}
