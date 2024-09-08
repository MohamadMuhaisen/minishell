/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 19:23:47 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/04 14:56:55 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	resolve_quotes(t_ll_node **lst, char *str,
		int *j, t_my_env *my_env)
{
	(*j)++;
	while (str[*j] && str[*j] != '"')
	{
		if (str[*j] == '$')
			search_and_add_var(lst, str, j, my_env);
		else
		{
			add_to_str(str[*j], lst);
			(*j)++;
		}
	}
	(*j)++;
}

void	resolve_literals(t_ll_node **lst, char *str, int *j)
{
	(*j)++;
	while (str[*j] && str[*j] != '\'')
	{
		add_to_str(str[*j], lst);
		(*j)++;
	}
	(*j)++;
}

void	replace_cleaned_str(t_ll_node **lst, t_ast_node *head, int i)
{
	int			len;
	t_ll_node	*cur;
	char		*str;

	len = 0;
	cur = *lst;
	while (cur)
	{
		cur = cur->next;
		len++;
	}
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return ;
	str[len] = '\0';
	len = 0;
	cur = *lst;
	while (cur)
	{
		str[len] = cur->c;
		cur = cur->next;
		len++;
	}
	free(head->arr[i]);
	head->arr[i] = str;
}

void	clean_quotations(t_ast_node *head, int i,
			t_my_env *my_env)
{
	t_ll_node	*start;
	int			j;

	start = NULL;
	j = 0;
	if (!ft_strchr(head->arr[i], '"') && !ft_strchr(head->arr[i], '\'')
		&& !ft_strchr(head->arr[i], '$'))
		return ;
	while (head->arr[i][j])
	{
		if (head->arr[i][j] == '"')
			resolve_quotes(&start, head->arr[i], &j, my_env);
		else if (head->arr[i][j] == '\'')
			resolve_literals(&start, head->arr[i], &j);
		else if (head->arr[i][j] == '$' && ((head->arr[i][j + 1] == '"')
				|| (head->arr[i][j + 1] == '\'')))
			j++;
		else if (head->arr[i][j] == '$')
			search_and_add_var(&start, head->arr[i], &j, my_env);
		else
			add_to_str(head->arr[i][j++], &start);
	}
	(replace_cleaned_str(&start, head, i), free_char_ll(&start));
}

void	traverse_and_clean_tree(t_ast_node *head,
			t_my_env *my_env)
{
	int	i;

	if (head->left)
		traverse_and_clean_tree(head->left, my_env);
	if (head->right)
		traverse_and_clean_tree(head->right, my_env);
	i = 0;
	if (head && head->arr)
	{
		while (head->arr[i])
		{
			clean_quotations(head, i, my_env);
			i++;
		}
	}
}
