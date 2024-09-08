/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sc_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:13:29 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/05 11:28:52 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_command_path(t_ast_node *node, t_my_env *my_env)
{
	char	*command_path;

	command_path = find_path(node->arr[0], my_env->env);
	if (!command_path && !node->heredoc)
	{
		if (access(node->arr[0], F_OK) == 0 && access(node->arr[0], X_OK) != 0)
		{
			ft_putstr_fd(node->arr[0], 2);
			ft_putendl_fd(": Permission denied", 2);
			my_env->exit_status = 126;
		}
		else
		{
			ft_putstr_fd(node->arr[0], 2);
			ft_putendl_fd(": command not found", 2);
			my_env->exit_status = 127;
		}
		exit(my_env->exit_status);
	}
	return (command_path);
}

void	handle_redirections_exec(t_ast_node *node)
{
	int	fd_in;
	int	fd_out;

	if (node->in)
	{
		fd_in = open_input_file(node->in);
		apply_input_redirection(fd_in);
	}
	if (node->out)
	{
		if (node->append)
			fd_out = open(node->out, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd_out = open(node->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out < 0)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}

void	execute_command(char *command_path, t_ast_node *node,
			t_my_env *my_env)
{
	if (command_path)
	{
		execve(command_path, node->arr, my_env->env);
		if (errno == EACCES)
		{
			perror(node->arr[0]);
			my_env->exit_status = 126;
		}
		else
		{
			perror("execve");
			my_env->exit_status = 1;
		}
	}
	else
	{
		ft_putstr_fd(node->arr[0], 2);
		ft_putendl_fd(": command not found", 2);
		my_env->exit_status = 127;
	}
	exit(my_env->exit_status);
}

void	handle_heredoc(t_ast_node *node)
{
	int	fd;

	if (node->heredoc)
	{
		fd = open(node->heredoc, O_RDONLY);
		if (fd < 0)
		{
			perror("open");
			return ;
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

void	execute_simple_command(t_ast_node *node,
			t_my_env *my_env)
{
	char		*command_path;
	struct stat	path_stat;

	if (!node || !node->arr || !node->arr[0] || !node->arr[0][0])
	{
		my_env->exit_status = 0;
		exit(my_env->exit_status);
	}
	if (stat(node->arr[0], &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd(node->arr[0], 2);
		ft_putendl_fd(": Is a directory", 2);
		my_env->exit_status = 126;
		exit(my_env->exit_status);
	}
	command_path = get_command_path(node, my_env);
	handle_heredoc(node);
	handle_redirections_exec(node);
	execute_command(command_path, node, my_env);
}
