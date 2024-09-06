/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:34:27 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/05 06:40:25 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*execute_pwd(void)
{
	char	*cwd;
	char	buffer[1024];

	cwd = getcwd(buffer, sizeof(buffer));
	if (cwd != NULL)
		return (cwd);
	else
		return (NULL);
}

void	update_env_oldpwd(char *old, t_my_env *my_env)
{
	if (!update_existing_env("OLDPWD", old, my_env))
		add_new_env_var("OLDPWD", old, my_env);
}

int	handle_cd_execution(char *arg, t_my_env *my_env, int *exit_status)
{
	int		ch;
	char	*old;

	old = execute_pwd();
	if (ft_strcmp(arg, "-") == 0)
		arg = get_env_var("$OLDPWD", my_env);
	if (arg && *arg == '\0')
	{
		printf("cd: OLDPWD not set\n");
		*exit_status = 1;
		return (1);
	}
	ch = chdir(arg);
	if (ch == 0)
	{
		update_env_oldpwd(old, my_env);
		*exit_status = 0;
		return (1);
	}
	perror("minishell");
	*exit_status = 1;
	return (1);
}

int	execute_cd(char *arg, t_my_env *my_env, int *exit_status)
{
	if (arg == NULL)
	{
		chdir("/home/mmuhaise/");
		*exit_status = 0;
		return (1);
	}
	return (handle_cd_execution(arg, my_env, exit_status));
}
