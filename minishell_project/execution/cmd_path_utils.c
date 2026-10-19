/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 16:53:48 by hsbeh             #+#    #+#             */
/*   Updated: 2026/05/08 18:05:00 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_the_path(char **the_path)
{
	int	i;

	i = 0;
	if (the_path == NULL)
		return ;
	while (the_path[i] != NULL)
	{
		free(the_path[i]);
		i++;
	}
	free(the_path);
}

char	*free_path_and_return_null(char **cmd_path)
{
	free_the_path(cmd_path);
	return (NULL);
}

char	*free_and_return_path(char **cmd_path, char *path_with_cmd)
{
	free_the_path(cmd_path);
	return (path_with_cmd);
}
