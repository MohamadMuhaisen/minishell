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
	while (input[i] == ' ')
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
	lstadd_back(tokens_ll, new_node);
	*i += t_len;
}
