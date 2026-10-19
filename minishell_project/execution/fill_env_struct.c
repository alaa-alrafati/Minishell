/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 23:40:57 by hsbeh             #+#    #+#             */
/*   Updated: 2026/05/16 12:53:43 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envir	*creat_new_env_node(char *env_value, char *env_key)
{
	t_envir	*new_env_node;

	new_env_node = ft_calloc(1, sizeof(t_envir));
	if (new_env_node == NULL)
		return (NULL);
	new_env_node->value = env_value;
	new_env_node->key = env_key;
	return (new_env_node);
}

void	link_node_from_end(t_envir **the_start_node, t_envir *new_node)
{
	t_envir	*temp_node;

	if (*the_start_node == NULL)
	{
		*the_start_node = new_node;
		return ;
	}
	temp_node = *the_start_node;
	while (temp_node->next != NULL)
		temp_node = temp_node->next;
	temp_node->next = new_node;
}

char	*allocate_and_fill_key(char *env_line)
{
	char	*env_key;
	int		key_len;
	int		j;

	key_len = 0;
	while (env_line[key_len] != '=' && env_line[key_len] != '\0')
		key_len++;
	env_key = malloc((key_len + 1) * sizeof(char));
	if (env_key == NULL)
		return (NULL);
	j = 0;
	while (j < key_len)
	{
		env_key[j] = env_line[j];
		j++;
	}
	env_key[j] = '\0';
	return (env_key);
}

int	get_value_and_key(char *env_line, t_envir **the_start_node)
{
	t_envir	*env;
	char	*ptr_to_equal_sign;
	char	*env_value;
	char	*env_key;

	ptr_to_equal_sign = ft_strchr(env_line, '=');
	if (ptr_to_equal_sign != NULL)
	{
		env_value = ft_strdup(ptr_to_equal_sign + 1);
		if (env_value == NULL)
			return (1);
		env_key = allocate_and_fill_key(env_line);
		if (env_key == NULL)
		{
			free(env_value);
			return (1);
		}
		env = creat_new_env_node(env_value, env_key);
		if (env == NULL)
			return (free_value_key_return_one(env_value, env_key));
		link_node_from_end(the_start_node, env);
	}
	return (0);
}

t_envir	*fill_envir_struct(char **envp)
{
	t_envir	*the_start_node;
	int		i;

	the_start_node = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		if (get_value_and_key(envp[i], &the_start_node) == 1)
		{
			free_env(the_start_node);
			return (NULL);
		}
		i++;
	}
	return (the_start_node);
}
