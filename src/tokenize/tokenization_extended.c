/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_extended.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:24:29 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/12/22 16:59:38 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_non_quote_token(char *input, t_elem **tokens_ll, int *i)
{
	int	t_len;

	t_len = token_len(input + *i);
	if (t_len > 0)
		create_token_node(tokens_ll, input, i, t_len);
}

int	handle_special_tokens(char *input, int i,
		t_elem **tokens_ll, t_my_env *my_env)
{
	if (input[i] && input[i] == '>' && input[i + 1] && input[i + 1] == '>')
	{
		lstadd_back(tokens_ll, create_elem(ft_strdup(">>")));
		return (i + 2);
	}
	else if (input[i] == '|')
	{
		if (input[i + 1] == '|')
		{
			ft_putendl_fd("Minishell: syntax", 2);
			ft_putendl_fd(" error near unexpected token `||`\n", 2);
			my_env->exit_status = 2;
			return (-1);
		}
		lstadd_back(tokens_ll, create_elem(ft_strdup("|")));
		return (i + 1);
	}
	else if (input[i] == '>')
	{
		lstadd_back(tokens_ll, create_elem(ft_strdup(">")));
		return (i + 1);
	}
	else if (input[i] && input[i] == '<'
		&& (!input[i + 1] || input[i + 1] != '<'))
	{
		lstadd_back(tokens_ll, create_elem(ft_strdup("<")));
		return (i + 1);
	}
	return (i);
}

void	tokenize_and_add(char *input, t_elem **tokens_ll, t_my_env *my_env)
{
	int		i;
	int		len;

	(void)my_env;
	i = 0;
	while (input[i])
	{
		i = skip_spaces(input, i);
		i = handle_special_tokens(input, i, tokens_ll, my_env);
		if (i == -1)
			return ;
		else
		{
			len = token_len(&input[i]);
			if (len > 0)
			{
				lstadd_back(tokens_ll,
					create_elem(ft_get_token(&input[i], len)));
				i += len;
			}
		}
	}
}

void	merge_adjacent_tokens(t_elem **tokens_ll)
{
	t_elem	*cur;
	t_elem	*tmp;
	char	*joined;

	cur = *tokens_ll;
	while (cur && cur->next)
	{
		if ((cur->token[strlen(cur->token) - 1] == '"'
				|| cur->token[strlen(cur->token) - 1] == '\'')
			&& (cur->next->token[0] == '"' || cur->next->token[0] == '\''))
		{
			joined = ft_strjoin(cur->token, cur->next->token);
			free(cur->token);
			cur->token = joined;
			tmp = cur->next;
			cur->next = cur->next->next;
			free(tmp->token);
			free(tmp);
		}
		else
		{
			cur = cur->next;
		}
	}
}

int	tokenize_input(char *input, t_elem **tokens_ll, t_my_env *my_env)
{
	t_elem	*a;

	a = *tokens_ll;
	tokenize_and_add(input, tokens_ll, my_env);
	while (a)
	{
		if ((a->token[0] == '<' && a->next == NULL))
		{
			return (0);
		}
		else if ((a->token[0] == '>' && a->next == NULL))
		{
			return (0);
		}
		a = a->next;
	}
	return (1);
}
/*
void merge_adjacent_tokens_heredoc(t_elem **tokens_ll)
{
	t_elem  *cur = *tokens_ll;
	t_elem  *tmp;
	char    *joined;

	while (cur && cur->next)
	{
		size_t cur_len = strlen(cur->token);

		// Check if current token ends with a quote and next token starts with a quote
		// AND ensure they were not separated by a space
		if ((cur->token[cur_len - 1] == '"' || cur->token[cur_len - 1] == '\'') &&
			(cur->next->token[0] == '"' || cur->next->token[0] == '\'') &&
			cur->space_after == 0)  // Ensure no space exists between tokens
		{
			// Merge the two tokens
			joined = ft_strjoin(cur->token, cur->next->token);
			free(cur->token);
			cur->token = joined;

			// Remove the next token from the linked list
			tmp = cur->next;
			cur->next = cur->next->next;
			free(tmp->token);
			free(tmp);
		}
		else
		{
			cur = cur->next;
		}
	}
}

*/

/*
void	merge_adjacent_tokens(t_elem **tokens_ll)
{
	t_elem	*cur;
	t_elem	*tmp;
	char	*joined;

	cur = *tokens_ll;
	while (cur && cur->next)
	{
		if (cur->token[strlen(cur->token) - 1] == '"'
			&& cur->next->token[0] == '"')
		{
			joined = ft_strjoin(cur->token, cur->next->token);
			free(cur->token);
			cur->token = joined;
			tmp = cur->next;
			cur->next = cur->next->next;
			free(tmp->token);
			free(tmp);
		}
		else
		{
			cur = cur->next;
		}
	}
}
*//*
void tokenize_and_add(char *input, t_elem **tokens_ll, t_my_env *my_env)
{
	(void)my_env; // Suppress unused parameter warning
	int i = 0;

	while (input[i])
	{
		// Skip leading spaces
		while (input[i] == ' ')
			i++;

		// Start of a new token
		int start = i;
		while (input[i] && input[i] != ' ') // Stop at the next space
			i++;

		if (i > start) // If we captured a non-empty token
		{
			create_token_node(tokens_ll, input, &start, i - start);

			// Get the last token to set `space_after`
			t_elem *last = *tokens_ll;
			while (last && last->next)
				last = last->next;

			if (last)
				last->space_after = (input[i] == ' '); // 1 if space follows, 0 otherwise
		}
	}
}

*/