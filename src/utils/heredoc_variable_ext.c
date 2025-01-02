/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_variable_ext.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 18:20:42 by mkaterji          #+#    #+#             */
/*   Updated: 2025/01/02 06:02:20 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*extract_var_name(char *input, int start, int *var_len)
{
	*var_len = 0;
	while (input[start + *var_len]
		&& (isalnum((unsigned char)input[start + *var_len])
			|| input[start + *var_len] == '_'))
		(*var_len)++;
	return (strndup(input + start, *var_len));
}

char	*find_var_value_in_env(char *var_name, int var_len, t_my_env *myenv)
{
	int	env_idx;

	env_idx = 0;
	while (myenv->env[env_idx])
	{
		if (!strncmp(myenv->env[env_idx], var_name, var_len)
			&& myenv->env[env_idx][var_len] == '=')
			return (strdup(myenv->env[env_idx] + var_len + 1));
		env_idx++;
	}
	return (NULL);
}
