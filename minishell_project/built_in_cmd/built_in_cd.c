/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 14:36:55 by hsbeh             #+#    #+#             */
/*   Updated: 2026/05/16 12:43:07 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	creat_and_add_pwd_key(t_envir **env, char *key, char *new_path)
{
	t_envir	*new_node;
	char	*temp_key;
	char	*temp_value;

	temp_key = ft_strdup(key);
	temp_value = ft_strdup(new_path);
	if (temp_key == NULL || temp_value == NULL)
	{
		free(temp_key);
		free(temp_value);
		perror("minishell: cd: malloc failed");
		return ;
	}
	new_node = creat_new_env_node(temp_value, temp_key);
	if (new_node == NULL)
	{
		free(temp_key);
		free(temp_value);
		perror("minishell: cd: malloc failed");
		return ;
	}
	link_node_from_end(env, new_node);
}

static void	update_pwd_in_our_env(t_envir **env, char *key, char *new_path)
{
	t_envir	*temp_env;
	int		key_len;

	temp_env = *env;
	key_len = ft_strlen(key) + 1;
	while (temp_env != NULL)
	{
		if (ft_strncmp(temp_env->key, key, key_len) == 0)
		{
			free(temp_env->value);
			temp_env->value = ft_strdup(new_path);
			if (temp_env->value == NULL)
				perror("minishell: cd: malloc failed");
			return ;
		}
		temp_env = temp_env->next;
	}
	creat_and_add_pwd_key(env, key, new_path);
}

char	*get_key_value_from_env(t_envir *env, char *key)
{
	int		key_len;

	if (env == NULL || key == NULL)
		return (NULL);
	key_len = ft_strlen(key) + 1;
	while (env != NULL)
	{
		if (ft_strncmp(env->key, key, key_len) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	read_new_path_and_update_old_path(t_envir **env, char *old_path)
{
	char	new_path[PATH_MAX];

	if (getcwd(new_path, sizeof(new_path)) == NULL)
	{
		perror("minishell: cd: getcwd failed");
		return ;
	}
	update_pwd_in_our_env(env, "OLDPWD", old_path);
	update_pwd_in_our_env(env, "PWD", new_path);
}

int	cd_cmd(t_envir **env, char **arg)
{
	char	old_path[PATH_MAX];

	if (getcwd(old_path, sizeof(old_path)) == NULL)
	{
		perror("minishell: cd: getcwd failed");
		return (1);
	}
	if (arg[1] == NULL)
		return (handle_cd_without_args(env, old_path));
	if (arg[2] != NULL)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (1);
	}
	if (chdir(arg[1]) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(arg[1]);
		return (1);
	}
	read_new_path_and_update_old_path(env, old_path);
	return (0);
}
