/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_tokenization_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:57:11 by mkaterji          #+#    #+#             */
/*   Updated: 2025/01/02 06:02:13 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == ' ');
}

int	handle_double_operator(char *input, int i)
{
	if ((input[i] == '<' && input[i + 1] == '<')
		|| (input[i] == '>' && input[i + 1] == '>'))
		return (i + 2);
	return (i);
}

char	update_quote_state(char quote, char current_char)
{
	if (!quote && (current_char == '\'' || current_char == '"'))
		return (current_char);
	if (quote == current_char)
		return ('\0');
	return (quote);
}
