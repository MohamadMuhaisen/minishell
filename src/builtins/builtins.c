/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:34:27 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/08 18:57:16 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_env_oldpwd(char *old, t_my_env *my_env)
{
	if (!update_existing_env("OLDPWD", old, my_env))
		add_new_env_var("OLDPWD", old, my_env);
}

int	change_directory(char *arg, t_my_env *my_env)
{
	int		ch;

	if (arg && *arg == '\0')
	{
		printf("cd: OLDPWD not set\n");
		my_env->exit_status = 1;
		return (1);
	}
	ch = chdir(arg);
	if (ch != 0)
	{
		perror("minishell");
		my_env->exit_status = 1;
		return (1);
	}
	return (0);
}

int	handle_cd_execution(char *arg, t_my_env *my_env)
{
	char	*old;
	char	buf[1024];
	char	*pwd;

	old = get_env_var("$PWD", my_env);
	if (ft_strcmp(arg, "-") == 0)
		arg = get_env_var("$OLDPWD", my_env);
	if (change_directory(arg, my_env) == 0)
	{
		pwd = getcwd(buf, sizeof(buf));
		update_env_oldpwd(old, my_env);
		if (!update_existing_env("PWD", pwd, my_env))
			add_new_env_var("PWD", pwd, my_env);
		my_env->exit_status = 0;
	}
	return (1);
}

int	execute_cd(char *arg, t_my_env *my_env)
{
	char	*old;
	char	buf[1024];
	char	*pwd;

	if (arg == NULL)
	{
		old = get_env_var("$PWD", my_env);
		update_env_oldpwd(old, my_env);
		chdir(get_env_var("$HOME", my_env));
		pwd = getcwd(buf, sizeof(buf));
		if (!update_existing_env("PWD", pwd, my_env))
			add_new_env_var("PWD", pwd, my_env);
		my_env->exit_status = 0;
		return (1);
	}
	return (handle_cd_execution(arg, my_env));
}
