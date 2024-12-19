/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:43:42 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/11 06:39:38 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal_exit_status = 0;

int	quotes_check(char *str)
{
	int		i;
	int		is_closed;
	char	quote;

	i = -1;
	is_closed = 1;
	while (str[++i])
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
		if (!str[i])
			break;
	}
	return (is_closed);
}

void	loop_utils(t_ast_node **ast_root, t_elem **tokens_ll,
			char **input, char **prompt)
{
	//cleanup_heredoc_file(*ast_root);
	free_tokens(*tokens_ll);
	*tokens_ll = NULL;
	free_ast(*ast_root);
	free(*input);
	free(*prompt);
}

void	process_input(char *input, char *prompt, t_my_env *my_env)
{
	t_elem		*tokens_ll;
	t_ast_node	*ast_root;

	tokens_ll = NULL;
	add_history(input);
	ft_check_signal(my_env);
	if (!tokenize_input(input, &tokens_ll, my_env))
	{
		free(tokens_ll);
		printf("syntax error near unexpected token `newline'\n");
		return ;
	}	
	ast_root = build_ast(tokens_ll, my_env);
	execute_ast(ast_root, my_env);
	loop_utils(&ast_root, &tokens_ll, &input, &prompt);
	free(tokens_ll);
}

void	prompt_loop(t_my_env *my_env)
{
	char		*input;
	char		*prompt;

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
			free(prompt);
			free(input);
			continue ;
		}
		process_input(input, prompt, my_env);
	}
}

int	main(int ac, char **av, char **env)
{
	t_my_env	*my_env;
	char		*shlvl;
	int			shlvl_value;
	char		cwd[1024];

	(void)ac;
	(void)av;
	my_env = malloc(sizeof(t_my_env));
	my_env->env = copy_env(env);
	shlvl = get_env_var("$SHLVL", my_env);
	if (shlvl)
	{
		shlvl_value = ft_atoi(shlvl) + 1;
		shlvl = ft_itoa(shlvl_value);
		update_existing_env("SHLVL", shlvl, my_env, 1);
	}
	else
		add_new_env_var("SHLVL", "1", my_env, 1);
	free(shlvl);
	add_new_env_var("PWD1", getcwd(cwd, sizeof(cwd)), my_env, 1);
	//add_new_env_var("OLDPWD1", "1", my_env, 1);
	if (!get_env_var("$PWD", my_env))
	{
		if (getcwd(cwd, sizeof(cwd))) // Get current working directory
			add_new_env_var("PWD", cwd, my_env, 1);
		else
			add_new_env_var("PWD", "/", my_env, 1); // Fallback to root if getcwd fails
	}
	if (!get_env_var("$OLDPWD", my_env))
	{
		add_new_env_var("OLDPWD", NULL, my_env, 0); // Add as unset
		add_new_env_var("OLDPWD1", NULL, my_env, 0);
	}
	else
		add_new_env_var("OLDPWD1", get_env_var("$OLDPWD", my_env), my_env, 1);
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