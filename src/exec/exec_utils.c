/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:13:20 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/03 15:14:02 by mmuhaise         ###   ########.fr       */
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
