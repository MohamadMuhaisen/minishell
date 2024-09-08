/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 21:45:54 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/05 11:23:20 by mmuhaise         ###   ########.fr       */
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

int	execute_exit(t_ast_node *node, t_my_env *my_env)
{
	int	exit_code;

	(void)my_env;
	if (node->arr[1] && !is_numeric_argument(node->arr[1]))
		exit_with_error(node->arr[1], my_env);
	if (node->arr[1] && node->arr[2])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		my_env->exit_status = 1;
		return (1);
	}
	else
	{
		if (node->arr[1])
			exit_code = ft_atoi(node->arr[1]);
		else
			exit_code = my_env->exit_status;
		my_env->exit_status = exit_code;
		exit(exit_code);
	}
	return (1);
}
