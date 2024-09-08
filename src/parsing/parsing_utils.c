/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:24:43 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/08 22:03:22 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_input_redirection(t_ast_node *node, char *filename)
{
	int	fd_in;

	fd_in = open(filename, O_RDONLY);
	if (fd_in < 0 && !node->err)
	{
		perror("open input");
		node->err = 1;
	}
	close(fd_in);
	if (node->in)
		free(node->in);
	node->in = ft_strdup(filename);
}

void	handle_output_redirection(t_ast_node *node, char *filename)
{
	int	fd_out;

	// filename = strip_quotes(filename);
	if (!node->err)
	{
		fd_out = open(filename, O_WRONLY | O_CREAT, 0644);
		if (fd_out < 0 && !node->err)
		{
			perror("open output");
			node->err = 1;
		}
		close(fd_out);
		if (node->out)
			free(node->out);
		node->out = ft_strdup(filename);
	}
}
