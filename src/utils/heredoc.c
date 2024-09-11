/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:13:10 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/11 06:34:19 by mmuhaise         ###   ########.fr       */
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

char	*generate_heredoc_filename(int x, pid_t pid)
{
	char	*filename;
	char	*pid_str;
	char	*strx;
	size_t	offset;

	strx = ft_itoa(x);
	pid_str = ft_itoa(pid);
	if (!strx || !pid_str)
	{
		free(strx);
		free(pid_str);
		return (NULL);
	}
	filename = malloc(64);
	if (!filename)
		return (NULL);
	ft_strlcpy(filename, strx, 64);
	offset = ft_strlen(strx);
	ft_strlcpy(filename + offset, pid_str, 64 - offset);
	ft_strlcat(filename, ".txt", 64);
	free(strx);
	free(pid_str);
	return (filename);
}

int	create_heredoc_file(char **filename)
{
	static int	x = -1;
	int			fd;
	pid_t		pid;

	x--;
	pid = getpid();
	*filename = generate_heredoc_filename(x, pid);
	if (!*filename)
		return (-1);
	fd = open(*filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(*filename);
		return (-1);
	}
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
	rl_redisplay();
	rl_done = 1;
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