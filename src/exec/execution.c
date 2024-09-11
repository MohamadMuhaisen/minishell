/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 14:34:15 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/11 06:28:49 by mmuhaise         ###   ########.fr       */
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

void	handle_fork_status(int status, t_my_env *my_env)
{
	int	sig;

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

void	execute_general_commands(t_ast_node *node, t_my_env *my_env)
{
	pid_t	pid;
	int		status;

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
			handle_fork_status(status, my_env);
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
