/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_extended.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:24:29 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/04 15:57:55 by mmuhaise         ###   ########.fr       */
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
	if (input[i] == '>' && input[i + 1] == '>')
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
	return (i);
}

void	tokenize_and_add(char *input, t_elem **tokens_ll, t_my_env *my_env)
{
	int		i;
	int		len;

	i = 0;
	while (input[i])
	{
		i = skip_spaces(input, i);
		i = handle_special_tokens(input, i, tokens_ll, my_env);
		if (i == -1)
			return ;
		else if (input[i] == '\'' || input[i] == '\"')
			handle_quotes(input, tokens_ll, &i);
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

void	tokenize_input(char *input, t_elem **tokens_ll, t_my_env *my_env)
{
	tokenize_and_add(input, tokens_ll, my_env);
	merge_adjacent_tokens(tokens_ll);
}
