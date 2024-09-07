/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:43:42 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/07 14:58:33 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal_exit_status = 0;

void	prompt_loop(t_my_env *my_env)
{
	char		*input;
	char		*prompt;
	t_elem		*tokens_ll;
	t_ast_node	*ast_root;
	int			exit_status;

	tokens_ll = NULL;
	exit_status = 0;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	while (1)
	{
		prompt = ft_strjoin("Minishell", "$ ");
		input = readline(prompt);
		if (!input)
		{
			free(prompt);
			break ;
		}
		add_history(input);
		tokenize_input(input, &tokens_ll, &exit_status);
		ast_root = build_ast(tokens_ll, my_env, &exit_status);
		execute_ast(ast_root, my_env, &exit_status);
		cleanup_heredoc_file(ast_root);
		free_tokens(tokens_ll);
		tokens_ll = NULL;
		free_ast(ast_root);
		free(input);
		free(prompt);
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