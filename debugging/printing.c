/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 18:50:35 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/09 04:13:00 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_indent(int level)
{
	for (int i = 0; i < level; i++)
		printf("    ");
}

void	print_ast(t_ast_node *node, int level)
{
	if (!node)
		return ;

	print_indent(level);

	if (node->type == PIPE)
		printf("PIPE Node\n");
	else if (node->type == SC)
	{
		printf("Simple Command (SC) Node:\n");
		print_indent(level + 1);
		printf("Arguments: ");
		if (node->arr)
		{
			for (int i = 0; node->arr[i]; i++)
				printf("%s ", node->arr[i]);
		}
		else
		{
			printf("None");
		}
		printf("\n");

		if (node->in)
		{
			print_indent(level + 1);
			printf("Input Redirect: %s\n", node->in);
		}
		if (node->out)
		{
			print_indent(level + 1);
			printf("Output Redirect: %s\n", node->out);
		}
	}

	if (node->left)
	{
		print_indent(level + 1);
		printf("Left Child:\n");
		print_ast(node->left, level + 2);
	}

	if (node->right)
	{
		print_indent(level + 1);
		printf("Right Child:\n");
		print_ast(node->right, level + 2);
	}
}

void print_ast_node(t_ast_node *node)
{
	int i;

	if (!node)
	{
		printf("Node is NULL.\n");
		return;
	}
	if (node->arr)
	{
		printf("arr: ");
		for (i = 0; node->arr[i] != NULL; i++)
			printf("[%s] ", node->arr[i]);
		printf("\n");
	}
	else
		printf("arr: NULL\n");
	printf("in: %s\n", node->in ? node->in : "NULL");
	printf("out: %s\n", node->out ? node->out : "NULL");
	printf("type: %d\n", node->type);
	printf("heredoc: %s\n", node->heredoc ? node->heredoc : "NULL");
	printf("append: %d\n", node->append);
	printf("err: %d\n", node->err);
	printf("ex_heredoc: %d\n", node->ex_heredoc);
	printf("left: %p\n", node->left);
	printf("right: %p\n", node->right);
	printf("\n");
}
