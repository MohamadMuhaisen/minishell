/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_extended.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaterji <mkaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 07:52:01 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/12/23 18:18:07 by mkaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_sigint_heredoc(int sig)
{
	g_signal_exit_status = sig;
	exit(130);
}

void	heredoc_input_loop(int fd, char *cleaned_limiter,
			t_my_env *myenv, int is_quoted)
{
	char	*input;
	char	*expanded_line;

	while (1)
	{
		input = readline("> ");
		if (!input || ft_strcmp(input, cleaned_limiter) == 0)
		{
			free(input);
			break ;
		}
		if (is_quoted)
		{
			write(fd, input, ft_strlen(input));
			write(fd, "\n", 1);
			free(input);
			continue ;
		}
		expanded_line = expand_line_heredoc(input, myenv);
		write(fd, expanded_line, ft_strlen(expanded_line));
		write(fd, "\n", 1);
		free(input);
		free(expanded_line);
	}
}

char	*expand_line_heredoc(char *line, t_my_env *myenv)
{
	int		in_s_q;
	char	*result;
	int		i;

	in_s_q = 0;
	result = ft_calloc(1, 1);
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			in_s_q = toggle_single_quotes_and_append(&result, line, i++);
		else if (line[i] == '$' && !in_s_q)
			handle_variable_expansion(&result, line, &i, myenv);
		else
			append_non_special_char(&result, line, &i);
	}
	return (result);
}

void	handle_heredoc_input(int fd, char *limiter,
			t_my_env *myenv, t_ast_node *node)
{
	int		is_quoted;
	char	*cleaned_limiter;

	signal(SIGINT, ft_sigint_heredoc);
	is_quoted = 0;
	if (ft_strchr(limiter, '\'') || ft_strchr(limiter, '"'))
		is_quoted = 1;
	cleaned_limiter = strip_quotes(limiter);
	heredoc_input_loop(fd, cleaned_limiter, myenv, is_quoted);
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
