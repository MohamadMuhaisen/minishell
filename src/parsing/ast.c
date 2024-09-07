/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:42:12 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/06 10:05:26 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_ast_node	*initialize_ast_root(t_elem *tokens_ll,
				t_my_env *my_env, int *exit_status)
{
	t_ast_node	*root;

	if (!tokens_ll)
		return (NULL);
	if (ft_strncmp(tokens_ll->token, "|", 1) == 0
		|| ft_strncmp(tokens_ll->token, ">", 1) == 0
		|| (ft_strncmp(tokens_ll->token, "<", 1) == 0 && !tokens_ll->next))
	{
		ft_putendl_fd("Minishell: syntax error", 2);
		*exit_status = 2;
		return (NULL);
	}
	root = parse_simple_command(&tokens_ll, my_env, exit_status);
	if (!root)
		return (NULL);
	return (root);
}

t_elem	*process_pipe_syntax(t_elem *tokens_ll,
		t_ast_node *root, int *exit_status)
{
	tokens_ll = tokens_ll->next;
	if (!tokens_ll || ft_strncmp(tokens_ll->token, "|", 1) == 0)
	{
		ft_putendl_fd("Minishell: syntax error", 2);
		free_ast(root);
		*exit_status = 2;
		return (NULL);
	}
	return (tokens_ll);
}

t_ast_node	*create_pipe_node(t_elem *tokens_ll,
		t_ast_node *root, t_my_env *my_env, int *exit_status)
{
	t_ast_node	*cur_node;

	cur_node = new_ast_node(PIPE);
	if (!cur_node)
	{
		free_ast(root);
		return (NULL);
	}
	cur_node->left = root;
	cur_node->right = build_ast(tokens_ll, my_env, exit_status);
	if (!cur_node->right)
	{
		free_ast(cur_node);
		return (NULL);
	}
	return (cur_node);
}

t_ast_node	*build_pipe_ast(t_elem *tokens_ll,
		t_ast_node *root, t_my_env *my_env, int *exit_status)
{
	t_ast_node	*cur_node;

	while (tokens_ll)
	{
		if (ft_strncmp(tokens_ll->token, "|", 1) == 0
			&& ft_strlen(tokens_ll->token) == 1)
		{
			tokens_ll = process_pipe_syntax(tokens_ll, root, exit_status);
			if (!tokens_ll)
				return (NULL);
			cur_node = create_pipe_node(tokens_ll, root, my_env, exit_status);
			return (cur_node);
		}
		tokens_ll = tokens_ll->next;
	}
	return (root);
}

t_ast_node	*build_ast(t_elem *tokens_ll, t_my_env *my_env, int *exit_status)
{
	t_ast_node	*root;

	root = initialize_ast_root(tokens_ll, my_env, exit_status);
	if (!root)
		return (NULL);
	return (build_pipe_ast(tokens_ll, root, my_env, exit_status));
}
