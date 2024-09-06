/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:21:48 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/04 15:48:43 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_get_token(const char *str, int len)
{
	char	*token;
	int		i;

	token = (char *)malloc((len + 1) * sizeof(char));
	if (!token)
		return (NULL);
	i = 0;
	while (i < len)
	{
		token[i] = str[i];
		i++;
	}
	token[len] = '\0';
	return (token);
}

int	token_len(char *input)
{
	int	i;

	i = 0;
	if (input[i] == '|' || input[i] == '<' || input[i] == '>')
	{
		if (input[i + 1] == input[i])
			return (2);
		return (1);
	}
	while (input[i] && input[i] != ' ' && input[i] != '|'
		&& input[i] != '<' && input[i] != '>')
		i++;
	return (i);
}

int	quote_len(char *input, int *i, int *len)
{
	int		closed;
	int		j;
	char	quote;

	closed = 0;
	*len = 0;
	quote = input[*i];
	if (!input[*i + 1])
		return (0);
	j = *i + 1;
	while (input[j] && !closed)
	{
		if (input[j] == quote)
		{
			closed = 1;
			(*len)--;
		}
		(*len)++;
		j++;
	}
	return (closed);
}

char	*allocate_and_fill_token(char *input, int *i, char quote, int len)
{
	char	*token;
	int		j;

	token = (char *)malloc((len + 2) * sizeof(char));
	if (!token)
		return (NULL);
	token[0] = quote;
	(*i)++;
	j = 1;
	while (input[*i] && j < len + 1)
	{
		token[j] = input[*i];
		(*i)++;
		j++;
	}
	token[j] = quote;
	token[j + 1] = '\0';
	return (token);
}

void	handle_quotes(char *input, t_elem **tokens_ll, int *i)
{
	t_elem	*new_node;
	int		len;
	char	*token;
	char	quote;

	quote = input[*i];
	if (quote_len(input, i, &len))
	{
		token = allocate_and_fill_token(input, i, quote, len);
		if (!token)
			return ;
		(*i)++;
		new_node = (t_elem *)malloc(sizeof(t_elem));
		if (!new_node)
		{
			free(token);
			return ;
		}
		new_node->token = token;
		new_node->next = NULL;
		lstadd_back(tokens_ll, new_node);
	}
}
