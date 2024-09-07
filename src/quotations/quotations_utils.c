/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotations_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:55:30 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/07 14:55:15 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_to_str(char c, t_ll_node **lst)
{
	t_ll_node	*new;
	t_ll_node	*cur;

	new = (t_ll_node *)malloc(sizeof(t_ll_node));
	new->c = c;
	new->next = NULL;
	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		cur = *lst;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
}

void	free_char_ll(t_ll_node **start)
{
	if (!*start)
		return ;
	if ((*start)->next)
		free_char_ll(&((*start)->next));
	free(*start);
}

void	expand_env_vars(t_ast_node *node, int i,
			t_my_env *my_env, int *exit_status)
{
	t_ll_node	*start;
	int			j;

	start = NULL;
	j = 0;
	while (node->arr[i][j])
	{
		if (node->arr[i][j] == '$')
			search_and_add_var(&start, node->arr[i], &j, my_env, exit_status);
		else
			add_to_str(node->arr[i][j++], &start);
	}
	replace_cleaned_str(&start, node, i);
	free_char_ll(&start);
}

void	add_to_str_str(char *str, t_ll_node **lst)
{
	int	i;

	i = 0;
	while (str[i])
	{
		add_to_str(str[i], lst);
		i++;
	}
}

void	handle_double_dollar(t_ll_node **lst)
{
	int		fd;
	char	buffer[12];
	char	*pid_str;
	int		i;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd < 0)
		return ;
	if (read(fd, buffer, sizeof(buffer) - 1) <= 0)
	{
		close(fd);
		return ;
	}
	buffer[11] = '\0';
	i = 0;
	while (buffer[i] && buffer[i] != ' ')
		i++;
	buffer[i] = '\0';
	pid_str = ft_strdup(buffer);
	add_to_str_str(pid_str, lst);
	free(pid_str);
	close(fd);
}
