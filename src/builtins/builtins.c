/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:34:27 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/12/21 13:22:26 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_env_oldpwd(char *old, t_my_env *my_env)
{
	update_existing_env("OLDPWD1", old, my_env, 1);
	if (!update_existing_env("OLDPWD", old, my_env, 1))
		add_new_env_var("OLDPWD", old, my_env, 1);
}

int	change_directory(char *arg, t_my_env *my_env)
{
	int		ch;

	if (arg && *arg == '\0')
	{
		ft_printf("cd: OLDPWD not set\n");
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
	char	*new_pwd;

	old = get_env_var("$PWD", my_env);
	if (ft_strcmp(arg, "-") == 0)
	{
		arg = get_env_var("$OLDPWD", my_env);
		if (!arg)
		{
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
			my_env->exit_status = 1;
			return (1);
		}
		ft_printf("%s\n", arg);
	}
	if (change_directory(arg, my_env) == 0)
	{
		pwd = getcwd(buf, sizeof(buf));
		if (!pwd)
		{
			ft_putstr_fd(CDERR, 2);
			pwd = get_env_var("$PWD1", my_env);
			if (pwd)
			{
				new_pwd = ft_strjoin(pwd, "/..");
				update_env_oldpwd(old, my_env);
				update_existing_env("PWD1", new_pwd, my_env, 1);
				if (!update_existing_env("PWD", new_pwd, my_env, 1))
					add_new_env_var("PWD", new_pwd, my_env, 1);
				free(new_pwd);
				my_env->exit_status = 0;
				return (1);
			}
			else
			{
				perror("cd");
				my_env->exit_status = 1;
				return (1);
			}
		}
		update_env_oldpwd(old, my_env);
		if (!update_existing_env("PWD", pwd, my_env, 1))
			add_new_env_var("PWD", pwd, my_env, 1);
		my_env->exit_status = 0;
	}
	else
	{
		perror("cd");
		my_env->exit_status = 1;
	}
	return (1);
}

int	execute_cd(char *arg, t_my_env *my_env)
{
	char	buf[1024];
	char	*pwd;
	char	*old;

	if (arg == NULL)
	{
		old = get_env_var("$PWD", my_env);
		update_env_oldpwd(old, my_env);
		if (chdir(get_env_var("$HOME", my_env)) != 0)
		{
			perror("cd");
			my_env->exit_status = 1;
			return (1);
		}
		pwd = getcwd(buf, sizeof(buf));
		update_existing_env("PWD1", pwd, my_env, 1);
		if (pwd && !update_existing_env("PWD", pwd, my_env, 1))
			add_new_env_var("PWD", pwd, my_env, 1);
		my_env->exit_status = 0;
		return (1);
	}
	return (handle_cd_execution(arg, my_env));
}
