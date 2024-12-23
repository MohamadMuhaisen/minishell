/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 21:45:54 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/12/23 17:21:40 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_numeric_argument(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (0);
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!isdigit(arg[i]))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

// void	exit_with_error(char *arg, t_my_env *my_env)
// {
// 	ft_putstr_fd("exit: ", 2);
// 	ft_putstr_fd(arg, 2);
// 	ft_putendl_fd(": numeric argument required", 2);
// 	my_env->exit_status = 2;
// 	exit(my_env->exit_status);
// }

long long	ft_atoll(const char *str, int *valid)
{
	long long	res;
	int			sign;

	res = 0;
	sign = 1;
	*valid = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while (*str && *str >= '0' && *str <= '9')
	{
		if (res > (LLONG_MAX - (*str - '0')) / 10)
		{
			*valid = 0;
			return (0);
		}
		res = res * 10 + (*str - '0');
		str++;
	}
	if (*str != '\0')
		*valid = 0;
	return (res * sign);
}

int	execute_exit(t_ast_node *node, t_my_env *my_env)
{
	long long	exit_code;
	int			valid;

	if (node->arr[1] && !is_numeric_argument(node->arr[1]))
		handle_invalid_numeric_argument(node->arr[1]);
	if (node->arr[1] && node->arr[2])
		return (handle_too_many_arguments(my_env));
	if (node->arr[1])
	{
		exit_code = ft_atoll(node->arr[1], &valid);
		if (!valid)
			return (1);
	}
	else
		exit_code = my_env->exit_status;
	my_env->exit_status = exit_code;
	exit(exit_code % 256);
	return (1);
}

// char	*expand_variable(char *input, int *i, t_my_env *myenv)
// {
// 	int		start;
// 	int		var_len;
// 	char	*var_name;
// 	char	*var_value;

// 	(void)myenv;
// 	start = *i + 1;
// 	var_len = 0;
// 	var_value = NULL;
// 	while (input[start + var_len]
// 		&& (isalnum((unsigned char)input[start + var_len])
// 			|| input[start + var_len] == '_'))
// 		var_len++;
// 	var_name = strndup(input + start, var_len);
// 	if (!var_name)
// 		return (strdup(""));
// 	*i = start + var_len;
// 	var_value = expand_var_loop(myenv, var_name, var_len, &var_value);
// 	printf("XXX%s\nXXX", var_value);
// 	free(var_name);
// 	if (!var_value)
// 		printf("helooooo\n");
// 	return (var_value);
// }

// char	*expand_var_loop(t_my_env *myenv, char *var_name,
// 			int var_len, char **var_value)
// {
// 	int		env_idx;
// 	char	*var_val;

// 	(void)var_value;
// 	env_idx = 0;
// 	while (myenv->env[env_idx])
// 	{
// 		if (!strncmp(myenv->env[env_idx], var_name, var_len)
// 			&& myenv->env[env_idx][var_len] == '=')
// 		{
// 			var_val = strdup(myenv->env[env_idx] + var_len + 1);
// 			break ;
// 		}
// 		env_idx++;
// 	}
// 	return (var_val);
// }