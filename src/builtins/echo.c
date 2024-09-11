/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 05:18:16 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/11 06:30:12 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_n_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	i = 1;
	while (str[++i])
	{
		if (str[i] != 'n')
			return (0);
	}
	return (1);
}

void	execute_echo(t_ast_node *node, t_my_env *my_env)
{
	int	i;
	int	no_newline;

	no_newline = 0;
	i = 1;
	while (node->arr[i] && is_n_flag(node->arr[i]))
	{
		no_newline = 1;
		i++;
	}
	while (node->arr[i])
	{
		ft_putstr_fd(node->arr[i], 1);
		if (node->arr[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!no_newline)
		ft_putchar_fd('\n', 1);
	my_env->exit_status = 0;
	exit(0);
}
