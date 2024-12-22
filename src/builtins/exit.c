/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaterji <mkaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 21:45:54 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/12/22 17:23:52 by mkaterji         ###   ########.fr       */
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
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

void	exit_with_error(char *arg, t_my_env *my_env)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	my_env->exit_status = 2;
	exit(my_env->exit_status);
}

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
		if (!valid || !validate_numeric_range(exit_code, node->arr[1]))
			return (1);
	}
	else
		exit_code = my_env->exit_status;
	my_env->exit_status = exit_code;
	exit(exit_code % 256);
	return (1);
}
