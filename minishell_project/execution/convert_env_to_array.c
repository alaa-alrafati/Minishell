/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env_to array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 00:45:47 by hsbeh             #+#    #+#             */
/*   Updated: 2026/05/07 01:15:43 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_env_node(t_envir *env)
{
	int	count;

	count = 0;
	while (env != NULL)
	{
		if (env->value != NULL)
			count++;
		env = env->next;
	}
	return (count);
}

static char	*create_env_line(t_envir *env)
{
	char	*temp_ptr;
	char	*env_line;

	temp_ptr = ft_strjoin(env->key, "=");
	if (temp_ptr == NULL)
		return (NULL);
	env_line = ft_strjoin(temp_ptr, env->value);
	if (env_line == NULL)
	{
		free(temp_ptr);
		return (NULL);
	}
	free(temp_ptr);
	return (env_line);
}

char	**convert_env_to_array(t_envir *env)
{
	char	**env_array;
	int		env_node_count;
	int		i;

	env_node_count = count_env_node(env);
	env_array = ft_calloc(env_node_count + 1, sizeof(char *));
	if (env_array == NULL)
		return (NULL);
	i = 0;
	while (env != NULL)
	{
		if (env->value != NULL)
		{
			env_array[i] = create_env_line(env);
			if (env_array[i] == NULL)
			{
				free_args(env_array);
				return (NULL);
			}
			i++;
		}
		env = env->next;
	}
	return (env_array);
}
