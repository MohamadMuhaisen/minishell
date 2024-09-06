/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_extended.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:59:11 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/03 21:08:18 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_new_env_var(char *key, char *value, t_my_env *my_env)
{
	int		env_count;
	char	**new_env;
	char	*tmp;
	int		j;

	env_count = count_env_vars(my_env->env);
	new_env = malloc((env_count + 2) * sizeof(char *));
	if (!new_env)
		return ;
	j = 0;
	while (j < env_count)
	{
		new_env[j] = my_env->env[j];
		j++;
	}
	new_env[env_count] = ft_strjoin(key, "=");
	tmp = new_env[env_count];
	new_env[env_count] = ft_strjoin(new_env[env_count], value);
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

int	execute_export(t_ast_node *node, t_my_env *my_env, int *exit_status)
{
	int		i;
	char	*key;
	char	*value;

	if (!node->arr[1])
		return (handle_no_args_export(my_env, exit_status));
	i = 1;
	while (node->arr[i])
	{
		if (parse_key_value(node->arr[i], &key, &value))
		{
			*exit_status = 1;
			return (1);
		}
		if (!update_existing_env(key, value, my_env))
			add_new_env_var(key, value, my_env);
		free(key);
		if (value)
			free(value);
		i++;
	}
	*exit_status = 0;
	return (1);
}
