/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:02:22 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/08 21:56:48 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>

extern int g_signal_exit_status;

typedef enum e_type{
	PIPE,
	SC,
}	t_type;

typedef struct s_elem {
	char			*token;
	struct s_elem	*next;
}	t_elem;

typedef struct s_ll_node {
	char				c;
	struct s_ll_node	*next;
}	t_ll_node;

typedef struct s_my_env {
	char	**env;
	int		exit_status;
}	t_my_env;

typedef struct s_ast_node {
	char				**arr;
	char				*in;
	char				*out;
	t_type				type;
	char				*heredoc;
	int					append;
	int					err;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

void		free_tokens(t_elem *tokens_ll);
int			execute_cd(char *arg, t_my_env *my_env);
void		ft_sigint_handler_beforecmd(int sig);
void		handle_sigquit(int sig);
void		prompt_loop(t_my_env *my_env);
void		lstadd_back(t_elem **lst, t_elem *new);
void		free_ast(t_ast_node *node);
t_ast_node	*build_ast(t_elem *tokens_ll, t_my_env *my_env);
void		print_ast(t_ast_node *node, int level);
t_ast_node	*new_ast_node(t_type type);
void		execute_ast(t_ast_node *node, t_my_env *my_env);
void		free_paths(char **paths);
void		print_env(t_my_env *my_env);
char		*find_path(char *command, char **env);
void		create_pipe(int pipefd[2]);
pid_t		fork_process(void);
void		execute_left_command(t_ast_node *node, t_my_env *my_env,
				int pipefd[2]);
void		execute_right_command(t_ast_node *node, t_my_env *my_env,
				int pipefd[2]);
void		close_pipe_and_wait(int pipefd[2], pid_t left_pid,
				pid_t right_pid, t_my_env *my_env);
void		execute_simple_command(t_ast_node *node,
				t_my_env *my_env);
void		handle_redirection(t_ast_node *node, t_elem **cur,
				t_my_env *my_env);
int			token_len(char *input);
void		handle_quotes(char *input, t_elem **tokens_ll, int *i);
char		*ft_get_token(const char *str, int len);
char		*get_env_var(char *str, t_my_env *my_env);
int			handle_builtins(t_ast_node *node, t_my_env *my_env);
int			execute_echo(t_ast_node *node, t_my_env *my_env, int *exit_status);
int			execute_export(t_ast_node *node, t_my_env *my_env);
int			count_env_vars(char **env);
char		**copy_env(char **env);
void		free_env(char **env_cpy);
int			handle_no_args_export(t_my_env *my_env);
int			parse_key_value(char *arg, char **key, char **value);
int			update_existing_env(char *key, char *value, t_my_env *my_env);
int			execute_unset(t_ast_node *node, t_my_env *my_env);
int			execute_exit(t_ast_node *node, t_my_env *my_env);
int			is_valid_identifier_export(const char *str);
t_elem		*create_elem(char *token);
void		handle_heredoc_token(char *input, t_elem **tokens_ll, int *i);
void		capture_heredoc(char *limiter, t_ast_node *node,
				t_my_env *myenv);
void		cleanup_heredoc_file(t_ast_node *node);
void		traverse_and_clean_tree(t_ast_node *head,
				t_my_env *my_env);
void		search_and_add_var(t_ll_node **lst, char *str,
				int *j, t_my_env *myenv);
void		add_new_env_var(char *key, char *value, t_my_env *my_env);
int			open_input_file(const char *filepath);
void		apply_input_redirection(int fd_in);
void		handle_input_redirection(t_ast_node *node, char *filename);
void		handle_output_redirection(t_ast_node *node, char *filename);
t_ast_node	*parse_simple_command(t_elem **tokens_ll,
				t_my_env *my_env);
void		tokenize_input(char *input, t_elem **tokens_ll, t_my_env *my_env);
void		add_to_str(char c, t_ll_node **lst);
void		free_char_ll(t_ll_node **start);
int			skip_spaces(char *input, int i);
void		create_token_node(t_elem **tokens_ll,
				char *input, int *i, int t_len);
void		free_ast_helper(t_ast_node *node);
void		clean_quotations(t_ast_node *head, int i,
				t_my_env *my_env);
void		expand_env_vars(t_ast_node *node, int i,
				t_my_env *my_env);
void		replace_cleaned_str(t_ll_node **lst, t_ast_node *head, int i);
void		handle_double_dollar(t_ll_node **lst);
void		ft_check_signal(t_my_env *my_env);
char		*strip_quotes(char *str);

#endif

// cat << '$USER' > out
// CTRL C in heredoc
// CTRL C in multiple minishells
// change PWD in env
// cat CTRL C exit code and general CTRL C exit code

// CTRL + C with old value

// cat < file1 | echo "hello world | file1 > file 2" > file2


// "cat"
// "<"
// "file1"
// "|"
// "echo"
// "hello world | file1 > file 2"
// ">"
// "file2"

// Basic Pipe Commands
// ls | wc
// echo hello | cat
// ps aux | grep bash
// who | wc -l
// cat /etc/passwd | grep root

// Pipes with Multiple Commands
// ls -l | grep '^d' | wc -l
// cat file1 | sort | uniq | wc -l
// ps aux | grep httpd | awk '{print $2}'
// find . -type f | xargs wc -l | sort -n
// ls -la | grep '^-' | sort -k 5 -n
// Pipes with Redirection

// cat file1.txt | grep 'pattern' > output.txt
// ls | tee file1.txt | wc -l
// echo "data" | tee file1.txt file2.txt | cat -n
// cat < input.txt | grep 'pattern' | sort > output.txt
// grep "error" < file1.txt | sort | uniq > output.txt ********
// Pipes with Quotes and Special Characters

// echo "hello | world" | cat
// echo 'single | quotes' | cat
// echo "|start and end|" | cat
// echo 'ls | wc' | bash
// echo 'ps aux | grep "httpd"' | sh
// Complex Commands with Pipes, Redirection, and Quotes

// cat file1 < file2 | grep 'pattern' > output.txt
// echo "pattern" | grep "pattern" | tee file.txt
// ls -la | grep '^d' | sort | uniq | wc -l
// cat file1.txt file2.txt | grep -v '^#' | sort | uniq > output.txt
// echo "content" | cat > file1.txt | wc -l
// Edge Cases

// cat file1 < file2 < file3 > file4 | grep "pattern" > file5
// cat <file1 | grep "pattern" | sort | uniq | wc -l
// echo "start" | tee >(grep "pattern" > file1.txt) >(sort > file2.txt)
// find . -type f -name "*.c" | xargs grep -H "main" | sort > results.txt
// cat <(ls | grep "^a") <(ls | grep "^b")
// Commands Mixing Pipes with Errors

// ls non_existing_file | wc -l
// grep "pattern" | sort | non_existing_command
// cat < non_existing_file | wc -l
// echo "hello" | non_existing_command
// non_existing_command | grep "pattern"