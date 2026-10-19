/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 16:52:22 by hsbeh             #+#    #+#             */
/*   Updated: 2026/05/08 16:56:46 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_the_path(char **envp)
{
	char	**the_path;
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (path == NULL)
		return (NULL);
	the_path = ft_split(path, ':');
	return (the_path);
}

static char	*helper_function(char *path, char *cmd)
{
	char	*add_slash_topath;
	char	*path_with_cmd;

	add_slash_topath = ft_strjoin(path, "/");
	if (add_slash_topath == NULL)
		return (NULL);
	path_with_cmd = ft_strjoin(add_slash_topath, cmd);
	free(add_slash_topath);
	return (path_with_cmd);
}

char	*check_cmd_path(char *cmd, char *envp[])
{
	char	**cmd_path;
	char	*path_with_cmd;
	int		i;

	if (ft_strchr(cmd, '/') != NULL)
		return (ft_strdup(cmd));
	cmd_path = get_the_path(envp);
	if (cmd_path == NULL)
		return (NULL);
	i = 0;
	while (cmd_path[i] != NULL)
	{
		path_with_cmd = helper_function(cmd_path[i], cmd);
		if (path_with_cmd == NULL)
			return (free_path_and_return_null(cmd_path));
		if (access(path_with_cmd, X_OK) == 0)
			return (free_and_return_path(cmd_path, path_with_cmd));
		free(path_with_cmd);
		i++;
	}
	return (free_path_and_return_null(cmd_path));
}
