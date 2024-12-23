/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaterji <mkaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:21:48 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/12/23 18:05:21 by mkaterji         ###   ########.fr       */
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
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	while (input[i])
	{
		if (!quote && is_special_char(input[i]))
			return (handle_double_operator(input, i));
		quote = update_quote_state(quote, input[i]);
		i++;
	}
	return (i);
}

// int quote_len(char *input, int *i, int *len)
// {
// 	int  closed;
// 	char quote;

// 	closed = 0;
// 	*len = 0;
// 	quote = input[*i];

// 	// Debug: Log the initial quote character and position
// 	printf("Starting quote_len: input[*i]=%c,
// 		quote=%c, index=%d\n", input[*i], quote, *i);

// 	if (!input[*i + 1]) // Check if quote is unclosed
// 	{
// 		printf("Unclosed quote detected at index %d\n", *i);
// 		return (0);
// 	}

// 	(*i)++; // Move past the opening quote
// 	while (input[*i] && !closed)
// 	{
// 		printf("Processing input[*i]=%c at index %d\n", input[*i], *i);

// 		if (input[*i] == quote) // Check for closing quote
// 		{
// 			closed = 1;
// 			printf("Closing quote found at index %d\n", *i);
// 		}
// 		else
// 		{
// 			(*len)++;
// 			printf("Increasing length: len=%d\n", *len);
// 		}
// 		(*i)++;
// 	}

// 	if (!closed)
// 		printf("Unclosed quote at end of string\n");

// 	return (closed);
// }

// char *allocate_and_fill_token(char *input, int *i, char quote, int len)
// {
// 	char *token;
// 	int   j;

// 	// Reserve space for the token plus two extra characters for quotes
// 	token = (char *)malloc((len + 3) * sizeof(char));
// 	if (!token)
// 		return (NULL);

// 	token[0] = quote; // Add opening quote
// 	j = 1;
// 	while (j <= len)
// 	{
// 		token[j] = input[*i];
// 		j++;
// 		(*i)++;
// 	}
// 	token[j++] = quote; // Add closing quote
// 	token[j] = '\0';
// 	return (token);
// }

// void	handle_quotes(char *input, t_elem **tokens_ll, int *i)
// {
// 	t_elem	*new_node;
// 	int		len;
// 	char	*token;
// 	char	quote;

// 	quote = input[*i];
// 	printf("Handling input: %s\n", input);
// 	if (quote_len(input, i, &len))
// 	{
// 		token = allocate_and_fill_token(input, i, quote, len);
// 		if (!token)
// 			return ;
// 		(*i)++;
// 		new_node = (t_elem *)malloc(sizeof(t_elem));
// 		if (!new_node)
// 		{
// 			free(token);
// 			return ;
// 		}
// 		new_node->token = token;
// 		new_node->next = NULL;
// 		lstadd_back(tokens_ll, new_node);
// 	}
// }
