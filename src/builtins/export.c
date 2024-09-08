/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:00:08 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/05 11:23:56 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	bubble_sort(char **array, int size)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(array[j], array[j + 1]) > 0)
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	print_sorted_env(t_my_env *my_env)
{
	int		env_count;
	int		i;
	char	**sorted_env;
	char	*equal_sign;

	env_count = count_env_vars(my_env->env);
	sorted_env = copy_env(my_env->env);
	bubble_sort(sorted_env, env_count);
	i = 0;
	while (i < env_count)
	{
		equal_sign = ft_strchr(sorted_env[i], '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			printf("declare -x %s=\"%s\"\n", sorted_env[i], equal_sign + 1);
			*equal_sign = '=';
		}
		else
		{
			printf("declare -x %s\n", sorted_env[i]);
		}
		i++;
	}
	free_env(sorted_env);
}

int	handle_no_args_export(t_my_env *my_env)
{
	print_sorted_env(my_env);
	my_env->exit_status = 0;
	return (1);
}

int	parse_key_value(char *arg, char **key, char **value)
{
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		*key = ft_substr(arg, 0, equal_sign - arg);
		*value = ft_strdup(equal_sign + 1);
	}
	else
	{
		*key = ft_strdup(arg);
		*value = NULL;
	}
	if (!is_valid_identifier_export(*key))
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": not a valid identifier", 2);
		free(*key);
		if (*value)
			free(*value);
		return (1);
	}
	return (0);
}

int	update_existing_env(char *key, char *value, t_my_env *my_env)
{
	int		j;
	char	*test;

	j = 0;
	while (my_env->env[j])
	{
		if (ft_strncmp(my_env->env[j], key, ft_strlen(key)) == 0
			&& my_env->env[j][ft_strlen(key)] == '=')
		{
			free(my_env->env[j]);
			test = ft_strjoin(key, "=");
			my_env->env[j] = test;
			my_env->env[j] = ft_strjoin(my_env->env[j], value);
			free(test);
			return (1);
		}
		j++;
	}
	return (0);
}
