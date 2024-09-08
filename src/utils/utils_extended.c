/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extended.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 10:33:33 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/08 20:53:48 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_ast_node	*new_ast_node(t_type type)
{
	t_ast_node	*node;

	node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->arr = NULL;
	node->in = NULL;
	node->out = NULL;
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	node->heredoc = NULL;
	node->append = 0;
	node->err = 0;
	return (node);
}

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

void	handle_sigquit(int sig)
{
	g_signal_exit_status = sig;
}

void	free_ast_helper(t_ast_node *node)
{
	free_ast(node->left);
	free_ast(node->right);
}

void	cleanup_heredoc_file(t_ast_node *node)
{
	if (node && node->heredoc)
	{
		if (remove(node->heredoc) != 0)
			perror("remove");
		free(node->heredoc);
		node->heredoc = NULL;
	}
}
