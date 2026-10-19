/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 23:45:36 by hsbeh             #+#    #+#             */
/*   Updated: 2026/05/16 12:45:34 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_and_print_unset_error(char *key)
{
	if (check_export_key_validation(key) == 1)
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(key, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	return (0);
}

static void	delete_the_head_node(t_envir **env)
{
	t_envir	*the_head;

	if (env == NULL || *env == NULL)
		return ;
	the_head = *env;
	*env = (*env)->next;
	free(the_head->key);
	free(the_head->value);
	free(the_head);
}

static void	delete_the_middle_node(t_envir *prev_node, t_envir *node_to_delete)
{
	if (node_to_delete == NULL || prev_node == NULL)
		return ;
	prev_node->next = node_to_delete->next;
	free(node_to_delete->key);
	free(node_to_delete->value);
	free(node_to_delete);
}

static void	remove_node_from_env(t_envir **env, char *key)
{
	t_envir	*temp_env;
	t_envir	*prev_node;
	int		key_len;

	if (env == NULL || *env == NULL || key == NULL)
		return ;
	key_len = ft_strlen(key) + 1;
	temp_env = *env;
	prev_node = NULL;
	if (ft_strncmp(key, temp_env->key, key_len) == 0)
	{
		delete_the_head_node(env);
		return ;
	}
	while (temp_env != NULL)
	{
		if (ft_strncmp(key, temp_env->key, key_len) == 0)
		{
			delete_the_middle_node(prev_node, temp_env);
			return ;
		}
		prev_node = temp_env;
		temp_env = temp_env->next;
	}
}

int	unset_cmd(t_envir **env, char **arg)
{
	int	status;
	int	i;

	if (arg[1] == NULL)
		return (0);
	i = 1;
	status = 0;
	while (arg[i] != NULL)
	{
		if (check_and_print_unset_error(arg[i]) == 1)
			status = 1;
		else
			remove_node_from_env(env, arg[i]);
		i++;
	}
	return (status);
}
