/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaterji <mkaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 19:01:12 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/12/22 17:10:21 by mkaterji         ###   ########.fr       */
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
}

void	print_env(t_my_env *my_env)
{
	int	i;

	i = 0;
	while (my_env->env[i])
	{
		if (ft_strncmp(my_env->env[i], "PWD1=", 5) != 0
			&& ft_strncmp(my_env->env[i], "OLDPWD1=", 8) != 0
			&& ft_strchr(my_env->env[i], '='))
		{
			ft_printf("%s\n", my_env->env[i]);
		}
		i++;
	}
}

void	change_i_helper(int *i, char *tofind)
{
	if (*tofind == '?')
		*i = 0;
}

void	prep_signals(void)
{
	signal(SIGINT, ft_sigint_handler_beforecmd);
	signal(SIGQUIT, handle_sigquit);
}
