/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:43:42 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/10 23:26:19 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal_exit_status = 0;

int	quotes_check(char *str)
{
	int		i;
	int		is_closed;
	char	quote;

	i = 0;
	is_closed = 1;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			is_closed = 0;
			i++;
			while (str[i])
			{
				if (str[i] == quote)
				{
					is_closed = 1;
					break ;
				}
				i++;
			}
		}
		i++;
	}
	return (is_closed);
}

void	loop_utils(t_ast_node **ast_root, t_elem **tokens_ll,
			char **input, char **prompt)
{
	cleanup_heredoc_file(*ast_root);
	free_tokens(*tokens_ll);
	*tokens_ll = NULL;
	free_ast(*ast_root);
	free(*input);
	free(*prompt);
}

void	prep_signals(void)
{
	signal(SIGINT, ft_sigint_handler_beforecmd);
	signal(SIGQUIT, handle_sigquit);
}


void	prompt_loop(t_my_env *my_env)
{
	char		*input;
	char		*prompt;
	t_elem		*tokens_ll;
	t_ast_node	*ast_root;

	tokens_ll = NULL;
	my_env->exit_status = 0;
	prep_signals();
	while (1)
	{
		prompt = ft_strjoin("Minishell", "$ ");
		input = readline(prompt);
		if (!input)
		{
			free(prompt);
			break ;
		}
		if (!quotes_check(input))
		{
			printf("Oops, you missed a quote :)\n");
			continue ;
		}
		add_history(input);
		ft_check_signal(my_env);
		tokenize_input(input, &tokens_ll, my_env);
		ast_root = build_ast(tokens_ll, my_env);
		execute_ast(ast_root, my_env);
		loop_utils(&ast_root, &tokens_ll, &input, &prompt);
	}
	free(tokens_ll);
}

int	main(int ac, char **av, char **env)
{
	t_my_env	*my_env;
	char		*shlvl;
	int			shlvl_value;

	(void)ac;
	(void)av;
	my_env = malloc(sizeof(t_my_env));
	my_env->env = copy_env(env);
	shlvl = get_env_var("$SHLVL", my_env);
	if (shlvl)
	{
		shlvl_value = ft_atoi(shlvl) + 1;
		shlvl = ft_itoa(shlvl_value);
		update_existing_env("SHLVL", shlvl, my_env);
	}
	else
		add_new_env_var("SHLVL", "3", my_env);
	free(shlvl);
	prompt_loop(my_env);
	free_env(my_env->env);
	free(my_env);
	return (0);
}

// printf("\nAST Structure:\n");
// print_ast(ast_root, 0);

// while (tokens_ll)
// {
// 	printf("%s -> ", tokens_ll->token);
// 	tokens_ll = tokens_ll->next;
// }