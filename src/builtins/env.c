/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:53:07 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/03 15:05:37 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_env_vars(char **env)
{
	int	count;

	count = 0;
	while (env[count])
		count++;
	return (count);
}

char	**allocate_env_copy(int env_count)
{
	char	**env_cpy;

	env_cpy = malloc((env_count + 1) * sizeof(char *));
	if (!env_cpy)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (env_cpy);
}

char	**copy_env(char **env)
{
	int		i;
	int		env_count;
	char	**env_cpy;

	env_count = count_env_vars(env);
	env_cpy = allocate_env_copy(env_count);
	i = 0;
	while (i < env_count)
	{
		env_cpy[i] = strdup(env[i]);
		if (!env_cpy[i])
		{
			perror("strdup");
			while (i > 0)
				free(env_cpy[--i]);
			free(env_cpy);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	env_cpy[env_count] = NULL;
	return (env_cpy);
}

void	free_env(char **env_cpy)
{
	int	i;

	i = 0;
	while (env_cpy[i])
		free(env_cpy[i++]);
	free(env_cpy);
}

char	*get_env_var(char *str, t_my_env *my_env)
{
	int		i;
	char	*var_name;
	int		var_len;

	i = 0;
	if (!str || str[0] != '$')
		return (NULL);
	var_name = str + 1;
	var_len = ft_strlen(var_name);
	while (my_env->env[i])
	{
		if (ft_strncmp(my_env->env[i], var_name, var_len) == 0
			&& my_env->env[i][var_len] == '=')
			return (my_env->env[i] + var_len + 1);
		i++;
	}
	return ("");
}
