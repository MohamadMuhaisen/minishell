/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:23:25 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/11 04:56:06 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	remove_env_var(char *key, t_my_env *my_env)
{
	int	i;
	int	j;
	int	key_len;

	i = 0;
	j = 0;
	key_len = ft_strlen(key);
	while (my_env->env[i])
	{
		if (ft_strcmp(my_env->env[i], key) == 0
			|| (ft_strncmp(my_env->env[i], key, key_len) == 0
				&& my_env->env[i][key_len] == '='))
			free(my_env->env[i]);
		else
			my_env->env[j++] = my_env->env[i];
		i++;
	}
	my_env->env[j] = NULL;
}

int	is_valid_identifier(char *key)
{
	int	i;

	if (!key || !ft_isalpha(key[0]))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	execute_unset(t_ast_node *node, t_my_env *my_env)
{
	int	i;

	i = 1;
	while (node->arr[i])
	{
		if (!is_valid_identifier(node->arr[i]))
		{
			ft_putstr_fd("unset: ", 2);
			ft_putstr_fd(node->arr[i], 2);
			ft_putendl_fd(": not a valid identifier", 2);
			my_env->exit_status = 1;
		}
		else
		{
			remove_env_var(node->arr[i], my_env);
			my_env->exit_status = 0;
		}
		i++;
	}
	return (1);
}
