/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_extended.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 07:52:01 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/11 01:27:42 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_sigint_heredoc(int sig)
{
	g_signal_exit_status = sig;
	exit(130);
}

void	heredoc_input_loop(int fd, char *cleaned_limiter,
			t_my_env *myenv)
{
	char		*input;
	t_ast_node	temp_node;

	while (1)
	{
		input = readline("> ");
		if (!input || ft_strcmp(input, cleaned_limiter) == 0)
		{
			free(input);
			break ;
		}
		temp_node.arr = malloc(sizeof(char *) * 2);
		temp_node.arr[0] = input;
		temp_node.arr[1] = NULL;
		expand_env_vars(&temp_node, 0, myenv);
		write(fd, temp_node.arr[0], ft_strlen(temp_node.arr[0]));
		write(fd, "\n", 1);
		free(temp_node.arr[0]);
		free(temp_node.arr);
	}
}

void	handle_heredoc_input(int fd, char *limiter,
			t_my_env *myenv, t_ast_node *node)
{
	char		*cleaned_limiter;

	signal(SIGINT, ft_sigint_heredoc);
	cleaned_limiter = strip_quotes(limiter);
	heredoc_input_loop(fd, cleaned_limiter, myenv);
	free(cleaned_limiter);
	signal(SIGINT, ft_sigint_handler_beforecmd);
	exit(node->ex_heredoc);
}

void	capture_heredoc(char *limiter, t_ast_node *node, t_my_env *myenv)
{
	int		fd;
	char	*filename;
	pid_t	pid;
	int		status;

	fd = create_heredoc_file(&filename);
	if (fd == -1)
	{
		perror("open");
		return ;
	}
	pid = fork();
	if (pid == 0)
		handle_heredoc_input(fd, limiter, myenv, node);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		node->ex_heredoc = 1;
	close(fd);
	node->heredoc = filename;
}
