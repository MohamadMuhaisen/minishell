/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 19:01:12 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/08 19:04:59 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_check_signal(t_my_env *my_env)
{
	if (g_signal_exit_status == SIGINT)
	{
		my_env->exit_status = 130;
		g_signal_exit_status = 0;
	}
	else if (g_signal_exit_status == SIGQUIT)
	{
		my_env->exit_status = 131;
		g_signal_exit_status = 0;
	}
}

void	print_env(t_my_env *my_env)
{
	int	i;

	i = 0;
	while (my_env->env[i])
	{
		printf("%s\n", my_env->env[i]);
		i++;
	}
}
