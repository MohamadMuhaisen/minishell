/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:29:56 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/07 19:24:38 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_elem	*lstlast(t_elem *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next)
	{
		lst = lst -> next;
	}
	return (lst);
}

void	lstadd_back(t_elem **lst, t_elem *new)
{
	t_elem	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		last = lstlast(*lst);
		last->next = new;
	}
}

void	free_tokens(t_elem *tokens_ll)
{
	t_elem	*temp;

	while (tokens_ll)
	{
		temp = tokens_ll;
		tokens_ll = tokens_ll->next;
		free(temp->token);
		free(temp);
	}
}

// void	handle_sigint(int sig)
// {
// 	char	*prompt;

// 	prompt = ft_strjoin("Minishell", "$ ");
// 	rl_redisplay();
// 	rl_replace_line("", 0);
// 	(void)sig;
// 	printf("\n%s", prompt);
// 	free(prompt);
// }

void	ft_sigint_handler_beforecmd(int sig)
{
	g_signal_exit_status = sig;
	rl_replace_line("", 0);
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_check_signal(int *exit_status)
{
	if (g_signal_exit_status == SIGINT)
	{
		*exit_status = 130;
		g_signal_exit_status = 0;
	}
	else if (g_signal_exit_status == SIGQUIT)
	{
		*exit_status = 131;
		g_signal_exit_status = 0;
	}
}

void	free_ast(t_ast_node *node)
{
	int	i;

	i = 0;
	if (!node)
		return ;
	if (node->arr)
	{
		while (node->arr[i])
		{
			free(node->arr[i]);
			i++;
		}
		free(node->arr);
	}
	if (node->in)
		free(node->in);
	if (node->out)
		free(node->out);
	if (node->heredoc)
	{
		free(node->heredoc);
		node->heredoc = NULL;
	}
	free_ast_helper(node);
	free(node);
}
