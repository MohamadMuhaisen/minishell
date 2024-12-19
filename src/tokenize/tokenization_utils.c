/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:53:11 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/04 15:53:57 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	skip_spaces(char *input, int i)
{
	//printf("Skipping spaces at index %d\n", i);
	while (input[i] && input[i] == ' ')
		i++;
	return (i);
}

void create_token_node(t_elem **tokens_ll, char *input, int *i, int t_len)
{
    t_elem *new_node;

    new_node = (t_elem *)malloc(sizeof(t_elem));
    if (!new_node)
        return;

    // Extract the token and set the next pointer
    new_node->token = ft_get_token(input + *i, t_len);
    new_node->next = NULL;
	//new_node->space_after = 0;
    // Check if there's a space immediately after the current token
    if (input[*i + t_len] == ' ')
        new_node->space_after = 1;
    else
        new_node->space_after = 0;

    // Add the new node to the linked list
    lstadd_back(tokens_ll, new_node);

    // Move the index forward by the token length
    *i += t_len;
}
void append_token(t_elem **tokens_ll, t_elem *new_token)
{
    t_elem *current = *tokens_ll;

    if (!current)
    {
        *tokens_ll = new_token;
        return;
    }

    while (current->next)
        current = current->next;

    current->next = new_token;
}
