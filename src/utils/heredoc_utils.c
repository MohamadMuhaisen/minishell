/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:55:06 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/12/23 17:22:50 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strjoin_char(char *s, char c)
{
	size_t	len;
	char	*new_str;

	if (!s)
	{
		new_str = malloc(2);
		if (!new_str)
			return (NULL);
		new_str[0] = c;
		new_str[1] = '\0';
		return (new_str);
	}
	len = strlen(s);
	new_str = malloc(len + 2);
	if (!new_str)
		return (NULL);
	strcpy(new_str, s);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	free(s);
	return (new_str);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new_str;
	size_t	len1;
	size_t	len2;

	len1 = 0;
	len2 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	new_str = malloc(len1 + len2 + 1);
	if (!new_str)
		return (NULL);
	if (s1)
		strcpy(new_str, s1);
	if (s2)
		strcpy(new_str + len1, s2);
	new_str[len1 + len2] = '\0';
	free(s1);
	return (new_str);
}

char	*expand_variable(char *input, int *i, t_my_env *myenv)
{
	int		start;
	int		var_len;
	char	*var_name;
	char	*var_value;
	int		env_idx;

	start = *i + 1;
	var_len = 0;
	var_value = NULL;
	while (input[start + var_len]
		&& (isalnum((unsigned char)input[start + var_len])
			|| input[start + var_len] == '_'))
		var_len++;
	var_name = strndup(input + start, var_len);
	if (!var_name)
		return (strdup(""));
	*i = start + var_len;
	env_idx = 0;
	while (myenv->env[env_idx])
	{
		if (!strncmp(myenv->env[env_idx], var_name, var_len)
			&& myenv->env[env_idx][var_len] == '=')
		{
			var_value = strdup(myenv->env[env_idx] + var_len + 1);
			break ;
		}
		env_idx++;
	}
	free(var_name);
	if (!var_value)
		return (strdup(""));
	return (var_value);
}
