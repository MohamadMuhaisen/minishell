/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:10:06 by mkaterji          #+#    #+#             */
/*   Updated: 2024/12/23 11:21:37 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_invalid_numeric_argument(char *arg)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	exit(2);
}

void	print_declare_x(char *env_var)
{
	char	*equal_sign;

	equal_sign = ft_strchr(env_var, '=');
	if (equal_sign)
	{
		*equal_sign = '\0';
		ft_printf("declare -x %s=\"%s\"\n", env_var, equal_sign + 1);
		*equal_sign = '=';
	}
	else
		ft_printf("declare -x %s\n", env_var);
}

int	validate_numeric_range(long long exit_code, char *arg)
{
	if (exit_code < 0 || exit_code > 255)
	{
		handle_invalid_numeric_argument(arg);
		return (0);
	}
	return (1);
}

int	handle_too_many_arguments(t_my_env *my_env)
{
	ft_putendl_fd("exit: too many arguments", 2);
	my_env->exit_status = 1;
	return (1);
}

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
