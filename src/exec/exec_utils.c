/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:13:20 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/11 06:28:55 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	open_input_file(const char *filepath)
{
	int	fd_in;

	fd_in = open(filepath, O_RDONLY);
	if (fd_in < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	return (fd_in);
}

void	apply_input_redirection(int fd_in)
{
	if (dup2(fd_in, STDIN_FILENO) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd_in);
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
