/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 05:43:39 by hsbeh             #+#    #+#             */
/*   Updated: 2026/05/16 12:47:35 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_export_key_validation(char *the_key)
{
	int	i;

	if (the_key == NULL || the_key[0] == '\0')
		return (1);
	if (ft_isalpha(the_key[0]) == 0 && the_key[0] != '_')
		return (1);
	i = 1;
	while (the_key[i] != '\0')
	{
		if (ft_isalnum(the_key[i]) == 0 && the_key[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

static int	count_env_list(t_envir *env)
{
	int	count;

	count = 0;
	while (env != NULL)
	{
		count++;
		env = env->next;
	}
	return (count);
}

static void	fill_env_in_array(t_envir *env, t_envir **env_array)
{
	int		i;

	i = 0;
	while (env != NULL)
	{
		env_array[i] = env;
		i++;
		env = env->next;
	}
}

static void	sort_env_array(t_envir **env_array, int env_list_count)
{
	t_envir	*temp;
	int		k_len;
	int		char_diff;
	int		i;
	int		x;

	i = 0;
	while (i < env_list_count)
	{
		x = i + 1;
		while (x < env_list_count)
		{
			k_len = ft_strlen(env_array[i]->key) + 1;
			char_diff = ft_strncmp(env_array[i]->key, env_array[x]->key, k_len);
			if (char_diff > 0)
			{
				temp = env_array[i];
				env_array[i] = env_array[x];
				env_array[x] = temp;
			}
			x++;
		}
		i++;
	}
}

int	sort_env(t_envir *env)
{
	t_envir	**env_array;
	int		env_list_count;

	env_list_count = count_env_list(env);
	if (env_list_count == 0)
		return (0);
	env_array = ft_calloc(env_list_count, sizeof(t_envir *));
	if (env_array == NULL)
	{
		ft_putendl_fd("minishell: export: malloc failed", 2);
		return (1);
	}
	fill_env_in_array(env, env_array);
	sort_env_array(env_array, env_list_count);
	print_export(env_array, env_list_count);
	free(env_array);
	return (0);
}
