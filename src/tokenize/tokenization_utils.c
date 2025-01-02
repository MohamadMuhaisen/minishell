/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:53:11 by mmuhaise          #+#    #+#             */
/*   Updated: 2025/01/02 06:02:15 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	skip_spaces(char *input, int i)
{
	while (input[i] && input[i] == ' ')
		i++;
	return (i);
}

void	create_token_node(t_elem **tokens_ll, char *input, int *i, int t_len)
{
	t_elem	*new_node;

	new_node = (t_elem *)malloc(sizeof(t_elem));
	if (!new_node)
		return ;
	new_node->token = ft_get_token(input + *i, t_len);
	new_node->next = NULL;
	if (input[*i + t_len] == ' ')
		new_node->space_after = 1;
	else
		new_node->space_after = 0;
	lstadd_back(tokens_ll, new_node);
	*i += t_len;
}

void	append_token(t_elem **tokens_ll, t_elem *new_token)
{
	t_elem	*current;

	current = *tokens_ll;
	if (!current)
	{
		*tokens_ll = new_token;
		return ;
	}
	while (current->next)
		current = current->next;
	current->next = new_token;
}

int	is_heredoc_context(t_elem **tokens_ll)
{
	t_elem	*current;

	current = *tokens_ll;
	while (current)
	{
		if (ft_strcmp(current->token, "<<") == 0)
		{
			return (1);
		}
		current = current->next;
	}
	return (0);
}
