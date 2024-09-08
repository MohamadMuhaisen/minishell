/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:13:10 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/08 19:03:28 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_elem	*create_elem(char *token)
{
	t_elem	*new_elem;

	new_elem = malloc(sizeof(t_elem));
	if (!new_elem)
		return (NULL);
	new_elem->token = token;
	new_elem->next = NULL;
	return (new_elem);
}

int	create_heredoc_file(char **filename)
{
	char	*pid_str;
	size_t	offset;
	pid_t	pid;
	int		fd;

	*filename = malloc(64);
	if (!*filename)
		return (-1);
	ft_strlcpy(*filename, "heredoc_temp_", 64);
	pid = getpid();
	pid_str = ft_itoa(pid);
	if (!pid_str)
	{
		free(*filename);
		return (-1);
	}
	offset = ft_strlen("heredoc_temp_");
	ft_strlcpy(*filename + offset, pid_str, 64 - offset);
	ft_strlcat(*filename, ".txt", 64);
	free(pid_str);
	fd = open(*filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		free(*filename);
	return (fd);
}

char	*strip_quotes(char *str)
{
	char	*cleaned;
	int		i;
	int		j;

	cleaned = malloc(ft_strlen(str) + 1);
	if (!cleaned)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '"' && str[i] != '\'')
			cleaned[j++] = str[i];
		i++;
	}
	cleaned[j] = '\0';
	return (cleaned);
}

void	ft_sigint_handler_incmd(int sig)
{
	g_signal_exit_status = sig;
	rl_replace_line("", 1);
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_done = 1;
}

void	handle_heredoc_input(int fd, char *limiter, t_my_env *myenv)
{
	char		*input;
	t_ast_node	temp_node;
	char		*cleaned_limiter;

	signal(SIGINT, ft_sigint_handler_incmd);
	cleaned_limiter = strip_quotes(limiter);
	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			free(cleaned_limiter);
			return ;
		}
		if (ft_strcmp(input, cleaned_limiter) == 0)
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
	free(cleaned_limiter);
	signal(SIGINT, ft_sigint_handler_beforecmd);
}

void	capture_heredoc(char *limiter, t_ast_node *node, t_my_env *myenv)
{
	int		fd;
	char	*filename;

	fd = create_heredoc_file(&filename);
	if (fd == -1)
	{
		perror("open");
		return ;
	}
	handle_heredoc_input(fd, limiter, myenv);
	close(fd);
	node->heredoc = filename;
}

/////////////////////////////////////////////

// void ft_handle_heredoc_child(t_data *data, int fd, char *limiter)
// {
// 	char *line;
// 	char *new_line;

// 	ft_reset_signal();
// 	line = readline("> ");
// 	while (line)
// 	{
// 		if (!line || ft_strcmp(line, limiter) == 0)
// 		{
// 			free(line);
// 			break;
// 		}
// 		if (ft_is_dollar(line, '$') && !data->quote_heredoc)
// 		{
// 			new_line = ft_change_variables(data, line, 0, 0);
// 			free(line);
// 			line = new_line;
// 		}
// 		write(fd, line, ft_strlen(line));
// 		write(fd, "\n", 1);
// 		free(line);
// 		line = readline("> ");
// 	}
// 	close(fd);
// 	exit(0);
// }

// int ft_handle_heredoc_parent(t_data *data, pid_t pid, int fd, char *limiter)
// {
// 	int status;

// 	waitpid(pid, &status, 0);
// 	if (data->stop_heredoc)
// 	{
// 		close(fd);
// 		unlink(limiter);
// 		return (1);
// 	}
// 	return (0);
// }

// void ft_here_doc(t_data *data, char *limiter)
// {
// 	int fd;
// 	pid_t pid;

// 	fd = open(limiter, O_CREAT | O_RDWR | O_TRUNC, 0644);
// 	if (fd == -1)
// 		return;
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		ft_handle_heredoc_child(data, fd, limiter);
// 	}
// 	else if (pid > 0)
// 	{
// 		if (ft_handle_heredoc_parent(data, pid, fd, limiter))
// 			return;
// 	}
// 	else
// 	{
// 		perror("fork");
// 		return;
// 	}
// 	return;
// }