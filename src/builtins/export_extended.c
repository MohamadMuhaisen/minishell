/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_extended.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:59:11 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/11 06:23:26 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**copy_existing_env_vars(char **env, int env_count)
{
	char	**new_env;
	int		j;

	new_env = malloc((env_count + 2) * sizeof(char *));
	if (!new_env)
		return (NULL);
	j = 0;
	while (j < env_count)
	{
		new_env[j] = env[j];
		j++;
	}
	return (new_env);
}

void	add_new_env_var(char *key, char *value, t_my_env *my_env, int has_equal)
{
	int		env_count;
	char	**new_env;
	char	*tmp;

	env_count = count_env_vars(my_env->env);
	new_env = copy_existing_env_vars(my_env->env, env_count);
	if (!new_env)
		return ;
	if (has_equal)
		new_env[env_count] = ft_strjoin(key, "=");
	else
		new_env[env_count] = ft_strjoin(key, "");
	tmp = new_env[env_count];
	if (value)
		new_env[env_count] = ft_strjoin(new_env[env_count], value);
	else
		new_env[env_count] = ft_strjoin(new_env[env_count], "");
	free(tmp);
	new_env[env_count + 1] = NULL;
	free(my_env->env);
	my_env->env = new_env;
}

int	is_valid_identifier_export(const char *str)
{
	if (!str || !(*str) || (!ft_isalpha(*str) && *str != '_'))
		return (0);
	str++;
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

void	process_export_var(char *arg, t_my_env *my_env, int *invalid)
{
	char	*key;
	char	*value;
	int		has_equal;

	if (ft_strchr(arg, '='))
		has_equal = 1;
	else
		has_equal = 0;
	if (parse_key_value(arg, &key, &value))
	{
		my_env->exit_status = 1;
		*invalid = 1;
		return ;
	}
	if (!update_existing_env(key, value, my_env, has_equal))
		add_new_env_var(key, value, my_env, has_equal);
	free(key);
	if (value)
		free(value);
}

int	execute_export(t_ast_node *node, t_my_env *my_env)
{
	int	i;
	int	invalid;

	invalid = 0;
	if (!node->arr[1])
		return (handle_no_args_export(my_env));
	i = 1;
	while (node->arr[i])
	{
		process_export_var(node->arr[i], my_env, &invalid);
		i++;
	}
	if (!invalid)
		my_env->exit_status = 0;
	return (1);
}
