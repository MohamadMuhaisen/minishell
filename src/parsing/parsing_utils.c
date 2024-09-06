/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:24:43 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/05 09:58:52 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_input_redirection(t_ast_node *node, char *filename)
{
	if (node->in)
		free(node->in);
	node->in = ft_strdup(filename);
}

void	handle_output_redirection(t_ast_node *node, char *filename)
{
	int	fd_out;

	fd_out = open(node->out, O_WRONLY | O_CREAT, 0644);
	close(fd_out);
	if (node->out)
		free(node->out);
	node->out = ft_strdup(filename);
}
