/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_extended.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaterji <mkaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:34:39 by mkaterji          #+#    #+#             */
/*   Updated: 2024/12/22 17:43:37 by mkaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialize_shell_level(t_my_env *my_env)
{
	char	*shlvl;
	int		shlvl_value;

	shlvl = get_env_var("$SHLVL", my_env);
	if (shlvl)
	{
		shlvl_value = ft_atoi(shlvl) + 1;
		shlvl = ft_itoa(shlvl_value);
		update_existing_env("SHLVL", shlvl, my_env, 1);
		free(shlvl);
	}
	else
		add_new_env_var("SHLVL", "1", my_env, 1);
}

void	initialize_cwd(t_my_env *my_env)
{
	char	cwd[1024];

	if (!getcwd(cwd, sizeof(cwd)))
		ft_strlcpy(cwd, "/", sizeof(cwd));
	add_new_env_var("PWD1", cwd, my_env, 1);
	if (!get_env_var("$PWD", my_env))
		add_new_env_var("PWD", cwd, my_env, 1);
}

void	initialize_oldpwd(t_my_env *my_env)
{
	char	*oldpwd;

	oldpwd = get_env_var("$OLDPWD", my_env);
	if (!oldpwd)
	{
		add_new_env_var("OLDPWD", NULL, my_env, 0);
		add_new_env_var("OLDPWD1", NULL, my_env, 0);
	}
	else
		add_new_env_var("OLDPWD1", oldpwd, my_env, 1);
}

int	find_closing_quote(char *str, char quote, int *i)
{
	(*i)++;
	while (str[*i])
	{
		if (str[*i] == quote)
			return (1);
		(*i)++;
	}
	return (0);
}
