/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_heredoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaterji <mkaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 18:13:20 by mkaterji          #+#    #+#             */
/*   Updated: 2024/12/23 18:19:30 by mkaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	toggle_single_quotes_and_append(char **result, char *line, int i)
{
	*result = ft_strjoin_char(*result, line[i]);
	return (!i);
}

void	handle_variable_expansion(char **result, char *line,
									int *i, t_my_env *myenv)
{
	char	*var_value;

	var_value = expand_variable(line, i, myenv);
	*result = ft_strjoin_free(*result, var_value);
	free(var_value);
}

void	append_non_special_char(char **result, char *line, int *i)
{
	*result = ft_strjoin_char(*result, line[*i]);
	(*i)++;
}
