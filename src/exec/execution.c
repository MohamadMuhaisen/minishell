/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 14:34:15 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/10 23:49:50 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute_pipe(t_ast_node *node, t_my_env *my_env)
{
	int		pipefd[2];
	pid_t	left_pid;
	pid_t	right_pid;

	create_pipe(pipefd);
	left_pid = fork_process();
	if (left_pid == 0)
		execute_left_command(node, my_env, pipefd);
	right_pid = fork_process();
	if (right_pid == 0)
		execute_right_command(node, my_env, pipefd);
	close_pipe_and_wait(pipefd, left_pid, right_pid, my_env);
}

int	handle_special_commands(t_ast_node *node, t_my_env *my_env)
{
	if (!node || !node->arr)
		return (0);
	if (node->arr[0])
	{
		if (ft_strcmp(node->arr[0], "echo") == 0
			|| ft_strcmp(node->arr[0], "cd") == 0
			|| ft_strcmp(node->arr[0], "pwd") == 0
			|| ft_strcmp(node->arr[0], "export") == 0
			|| ft_strcmp(node->arr[0], "unset") == 0
			|| ft_strcmp(node->arr[0], "env") == 0
			|| ft_strcmp(node->arr[0], "exit") == 0)
		{
			return (handle_builtins(node, my_env));
		}
	}
	return (0);
}

void	execute_general_commands(t_ast_node *node, t_my_env *my_env)
{
	int		status;
	int		sig;
	pid_t	pid;

	if (!node)
		return ;
	if (node->type == SC)
	{
		pid = fork();
		if (pid == 0)
			execute_simple_command(node, my_env);
		else if (pid > 0)
		{
			waitpid(pid, &status, 0);
			if (WIFSIGNALED(status))
			{
				sig = WTERMSIG(status);
				if (sig == SIGQUIT)
					my_env->exit_status = 128 + SIGQUIT;
				else if (sig == SIGINT)
					my_env->exit_status = 128 + SIGINT;
			}
			else if (WIFEXITED(status))
				my_env->exit_status = WEXITSTATUS(status);
			else
				my_env->exit_status = 1;
		}
	}
	else if (node->type == PIPE)
		execute_pipe(node, my_env);
}

void	execute_ast(t_ast_node *node, t_my_env *my_env)
{
	if (!node)
		return ;
	traverse_and_clean_tree(node, my_env);
	if (!handle_special_commands(node, my_env))
		execute_general_commands(node, my_env);
}

int	handle_builtins(t_ast_node *node, t_my_env *my_env)
{
	if (ft_strcmp(node->arr[0], "env") == 0)
	{
		print_env(my_env);
		return (1);
	}
	else if (ft_strcmp(node->arr[0], "cd") == 0)
	{
		if (node->arr[1] && node->arr[2])
		{
			my_env->exit_status = 1;
			ft_putstr_fd(node->arr[0], 2);
			ft_putendl_fd(": too many arguments", 2);
			return (1);
		}
		else
			return (execute_cd(node->arr[1], my_env));
	}
	else if (ft_strcmp(node->arr[0], "export") == 0)
		return (execute_export(node, my_env));
	else if (ft_strcmp(node->arr[0], "unset") == 0)
		return (execute_unset(node, my_env));
	else if (ft_strcmp(node->arr[0], "exit") == 0)
		return (execute_exit(node, my_env));
	return (0);
}

// int	execute_echo(t_ast_node *node, t_my_env *my_env, int *exit_status)
// {
// 	(void)my_env;
// 	printf("X%sX S%sS\n", node->arr[0], node->arr[1]);
// 	if (ft_strcmp(node->arr[0], "echo") == 0 && node->arr[1]
// 		&& ft_strncmp(node->arr[1], "$?", 2) == 0)
// 	{
// 		printf("%d", *exit_status);
// 		if (ft_strlen(node->arr[1]) > 2)
// 			printf("%s\n", node->arr[1] + 2);
// 		else
// 			printf("\n");
// 		return (1);
// 	}
// 	// else if (ft_strcmp(node->arr[0], "echo") == 0 && node->arr[1]
// 	// 	&& ft_strncmp(node->arr[1], "$", 1) == 0 && ft_strlen(node->arr[1]) > 1)
// 	// {
// 	// 	printf("%s\n", get_env_var(node->arr[1], my_env));
// 	// 	return (1);
// 	// }
// 	return (0);
// }
