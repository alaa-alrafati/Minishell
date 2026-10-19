/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 19:33:44 by hsbeh             #+#    #+#             */
/*   Updated: 2026/05/16 12:44:51 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	without_equal(t_envir **env, char *the_key, int the_key_len)
{
	t_envir	*temp_env;
	t_envir	*new_node;

	temp_env = *env;
	while (temp_env != NULL)
	{
		if (ft_strncmp(the_key, temp_env->key, the_key_len) == 0)
		{
			free(the_key);
			return (0);
		}
		temp_env = temp_env->next;
	}
	new_node = creat_new_env_node(NULL, the_key);
	if (new_node == NULL)
	{
		free(the_key);
		return (1);
	}
	link_node_from_end(env, new_node);
	return (0);
}

static int	with_equal(t_envir **env, char *key, char *new_value, int key_len)
{
	t_envir	*temp_env;
	t_envir	*new_node;

	temp_env = *env;
	while (temp_env != NULL)
	{
		if (ft_strncmp(key, temp_env->key, key_len) == 0)
		{
			free(temp_env->value);
			temp_env->value = new_value;
			free(key);
			return (0);
		}
		temp_env = temp_env->next;
	}
	new_node = creat_new_env_node(new_value, key);
	if (new_node == NULL)
	{
		free(key);
		free(new_value);
		return (1);
	}
	link_node_from_end(env, new_node);
	return (0);
}

static int	check_export_key_in_env(char *key, char *arg_line, t_envir **env)
{
	char	*new_env_value;
	char	*ptr_to_equal_sign;
	int		the_key_len;

	the_key_len = ft_strlen(key) + 1;
	ptr_to_equal_sign = ft_strchr(arg_line, '=');
	if (ptr_to_equal_sign != NULL)
	{
		new_env_value = ft_strdup(ptr_to_equal_sign + 1);
		if (new_env_value == NULL)
		{
			free(key);
			return (1);
		}
		return (with_equal(env, key, new_env_value, the_key_len));
	}
	else
		return (without_equal(env, key, the_key_len));
}

static void	print_erorr_free_set_status(char *arg, char *key, int *status)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	free(key);
	*status = 1;
}

int	export_cmd(char **arg, t_envir **env)
{
	char	*the_key;
	int		status;
	int		i;

	if (arg[1] == NULL)
		return (sort_env(*env));
	i = 1;
	status = 0;
	while (arg[i] != NULL)
	{
		the_key = allocate_and_fill_key(arg[i]);
		if (the_key == NULL)
			return (1);
		if (check_export_key_validation(the_key) == 1)
			print_erorr_free_set_status(arg[i], the_key, &status);
		else
		{
			if (check_export_key_in_env(the_key, arg[i], env) == 1)
				status = 1;
		}
		i++;
	}
	return (status);
}
