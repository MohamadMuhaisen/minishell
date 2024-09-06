/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_extended.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:20:57 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/05 11:02:20 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

char	*clean_filename(const char *filename)
{
	char	*cleaned_filename;
	size_t	i;
	size_t	j;
	size_t	len;

	len = 0;
	i = 0;
	while (filename[i])
	{
		if (!is_quote(filename[i]))
			len++;
		i++;
	}
	cleaned_filename = (char *)malloc(len + 1);
	if (!cleaned_filename)
		return (NULL);
	j = 0;
	i = 0;
	while (filename[i])
	{
		if (!is_quote(filename[i]))
			cleaned_filename[j++] = filename[i];
		i++;
	}
	return (cleaned_filename[j] = '\0', cleaned_filename);
}

char	*get_filename(t_elem **cur, char *redirection_token)
{
	char	*filename;
	char	*temp;

	filename = NULL;
	if (ft_strcmp(redirection_token, ">>") == 0
		|| ft_strcmp(redirection_token, ">") == 0
		|| ft_strcmp(redirection_token, "<") == 0
		|| ft_strcmp(redirection_token, "<<") == 0)
	{
		*cur = (*cur)->next;
		if (*cur)
			temp = ft_strdup((*cur)->token);
		else
			temp = NULL;
	}
	else
		temp = ft_strdup(redirection_token);
	if (temp)
		filename = clean_filename(temp);
	free(temp);
	return (filename);
}

void	handle_redirection(t_ast_node *node, t_elem **cur,
			t_my_env *my_env, int *exit_status)
{
	char	*redirection_token;
	char	*filename;

	node->append = 0;
	redirection_token = (*cur)->token;
	filename = get_filename(cur, redirection_token);
	if (ft_strcmp(redirection_token, ">>") == 0)
	{
		node->append = 1;
		handle_output_redirection(node, filename);
	}
	else if (ft_strcmp(redirection_token, "<<") == 0)
	{
		if (*cur)
			capture_heredoc((*cur)->token, node, my_env, exit_status);
	}
	else if (ft_strcmp(redirection_token, "<") == 0)
		handle_input_redirection(node, filename);
	else if (ft_strcmp(redirection_token, ">") == 0)
	{
		node->append = 0;
		handle_output_redirection(node, filename);
	}
	if (filename)
		free(filename);
}
