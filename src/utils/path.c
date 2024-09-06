/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:15:56 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/03 20:53:25 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**extract_and_split_path(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	while (env[i] && ft_strnstr(env[i], "PATH=", 5) == 0)
		i++;
	if (!env[i])
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

char	*search_command_in_directories(char *command, char **paths)
{
	char	*path;
	char	*mini_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		mini_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(mini_path, command);
		free(mini_path);
		if (path)
		{
			if (access(path, F_OK | X_OK) == 0)
			{
				free_paths(paths);
				return (path);
			}
		}
		free(path);
		i++;
	}
	return (NULL);
}

char	*check_command_path(char *command)
{
	if (command && ft_strchr(command, '/') != NULL)
	{
		if (access(command, F_OK) == 0)
		{
			if (access(command, X_OK) == 0)
				return (ft_strdup(command));
			else
				return (NULL);
		}
		return (NULL);
	}
	return (NULL);
}

char	*search_command_in_path(char *command, char **env)
{
	char	**paths;
	char	*path;

	paths = extract_and_split_path(env);
	if (!paths)
		return (NULL);
	path = search_command_in_directories(command, paths);
	if (!path)
		free_paths(paths);
	return (path);
}

char	*find_path(char *command, char **env)
{
	char	*path;

	path = check_command_path(command);
	if (path != NULL)
		return (path);
	return (search_command_in_path(command, env));
}
