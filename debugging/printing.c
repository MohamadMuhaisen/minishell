/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 18:50:35 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/08 19:04:52 by mmuhaise         ###   ########.fr       */
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
