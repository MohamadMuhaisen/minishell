/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 18:38:22 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/07 14:59:26 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_sc_args(t_elem **tokens_ll)
{
	t_elem	*cur;
	int		arg_count;

	if (!tokens_ll || !*tokens_ll)
		return (0);
	cur = *tokens_ll;
	arg_count = 0;
	while (cur && ft_strncmp(cur->token, "|", 1) != 0)
	{
		if (ft_strncmp(cur->token, "<", 1) != 0
			&& ft_strncmp(cur->token, ">", 1) != 0)
		{
			arg_count++;
		}
		cur = cur->next;
	}
	return (arg_count);
}

t_ast_node	*init_ast_node_and_allocate_args(t_elem **tokens_ll, int *arg_count)
{
	t_ast_node	*node;

	if (!tokens_ll || !*tokens_ll)
		return (NULL);
	*arg_count = count_sc_args(tokens_ll);
	node = new_ast_node(SC);
	if (!node)
		return (NULL);
	node->arr = (char **)malloc(sizeof(char *) * (*arg_count + 1));
	if (!node->arr)
	{
		free(node);
		return (NULL);
	}
	return (node);
}

t_ast_node	*initialize_command_node(t_elem **tokens_ll, int *arg_count)
{
	t_ast_node	*node;

	if (!tokens_ll || !*tokens_ll)
		return (NULL);
	node = init_ast_node_and_allocate_args(tokens_ll, arg_count);
	if (!node)
		return (NULL);
	return (node);
}

// cur = cur ? cur->next : NULL;
t_ast_node	*fill_command_node(t_ast_node *node, t_elem **tokens_ll,
				t_my_env *my_env)
{
	t_elem	*cur;
	int		i;

	cur = *tokens_ll;
	i = 0;
	while (cur && ft_strncmp(cur->token, "|", 1) != 0)
	{
		if (ft_strncmp(cur->token, "<", 1) == 0
			|| ft_strncmp(cur->token, ">", 1) == 0)
			handle_redirection(node, &cur, my_env);
		else
		{
			node->arr[i++] = ft_strdup(cur->token);
			if (!node->arr[i - 1])
			{
				free_ast(node);
				return (NULL);
			}
		}
		cur = cur->next;
	}
	node->arr[i] = NULL;
	*tokens_ll = cur;
	return (node);
}

t_ast_node	*parse_simple_command(t_elem **tokens_ll,
				t_my_env *my_env)
{
	t_ast_node	*node;
	int			arg_count;

	node = initialize_command_node(tokens_ll, &arg_count);
	if (!node)
		return (NULL);
	return (fill_command_node(node, tokens_ll, my_env));
}
