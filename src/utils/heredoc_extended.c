/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_extended.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 07:52:01 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/11 01:27:42 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_sigint_heredoc(int sig)
{
	g_signal_exit_status = sig;
	exit(130);
}

void heredoc_input_loop(int fd, char *cleaned_limiter,
			t_my_env *myenv, int is_quoted)
{
    char        *input;
    char        *expanded_line;

    while (1)
    {
        input = readline("> ");
        if (!input || ft_strcmp(input, cleaned_limiter) == 0)
        {
            free(input);
            break ;
        }
        //printf("SDWAD");
        if (is_quoted)
        {
            // If the delimiter is quoted, no expansions
            write(fd, input, ft_strlen(input));
            write(fd, "\n", 1);
            free(input);
            continue;
        }

        // If delimiter is not quoted, handle expansions manually.
        // This logic will parse the line and expand only when not in single quotes.
        expanded_line = expand_line_heredoc(input, myenv);
        write(fd, expanded_line, ft_strlen(expanded_line));
        write(fd, "\n", 1);
        free(input);
        free(expanded_line);
    }
}

char *expand_line_heredoc(char *line, t_my_env *myenv)
{
    int in_single_quotes = 0;
    char *result = ft_calloc(1, 1); // start with empty string
    int i = 0;

    while (line[i])
    {
        if (line[i] == '\'')
        {
            in_single_quotes = !in_single_quotes;
            // Add the single quote to the result as literal
            result = ft_strjoin_char(result, line[i]);
            i++;
        }
        else if (line[i] == '$' && !in_single_quotes)
        {
            // Perform variable expansion
            char *var_value = expand_variable(line, &i, myenv);
            result = ft_strjoin_free(result, var_value);
            free(var_value);
        }
        else
        {
            // Just copy the character
            result = ft_strjoin_char(result, line[i]);
            i++;
        }
    }

    return result;
}


void	handle_heredoc_input(int fd, char *limiter,
			t_my_env *myenv, t_ast_node *node)
{
	int		is_quoted;
	char	*cleaned_limiter;

	signal(SIGINT, ft_sigint_heredoc);

	// Check if any quotes are present
	is_quoted = (ft_strchr(limiter, '\'') || ft_strchr(limiter, '"')) ? 1 : 0;

	// Now strip the quotes from the delimiter
	cleaned_limiter = strip_quotes(limiter);

	// Pass the is_quoted flag to your heredoc_input_loop
	// If quoted, heredoc_input_loop won't perform expansions.
	heredoc_input_loop(fd, cleaned_limiter, myenv, is_quoted);

	free(cleaned_limiter);
	signal(SIGINT, ft_sigint_handler_beforecmd);
	exit(node->ex_heredoc);
}


void	capture_heredoc(char *limiter, t_ast_node *node, t_my_env *myenv)
{
	int		fd;
	char	*filename;
	pid_t	pid;
	int		status;

	fd = create_heredoc_file(&filename);
	if (fd == -1)
	{
		perror("open");
		return ;
	}
	pid = fork();
	if (pid == 0)
		handle_heredoc_input(fd, limiter, myenv, node);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		node->ex_heredoc = 1;
	close(fd);
	node->heredoc = filename;
}
char *ft_strjoin_char(char *s, char c)
{
    size_t len;
    char *new_str;

    if (!s)
    {
        new_str = malloc(2);
        if (!new_str)
            return NULL;
        new_str[0] = c;
        new_str[1] = '\0';
        return new_str;
    }
    len = strlen(s);
    new_str = malloc(len + 2);
    if (!new_str)
        return NULL;
    strcpy(new_str, s);
    new_str[len] = c;
    new_str[len + 1] = '\0';
    free(s);
    return new_str;
}

char *ft_strjoin_free(char *s1, char *s2)
{
    char *new_str;
    size_t len1 = s1 ? strlen(s1) : 0;
    size_t len2 = s2 ? strlen(s2) : 0;

    new_str = malloc(len1 + len2 + 1);
    if (!new_str)
        return NULL;
    if (s1)
        strcpy(new_str, s1);
    if (s2)
        strcpy(new_str + len1, s2);
    new_str[len1 + len2] = '\0';

    free(s1);
    return new_str;
}
char *expand_variable(char *input, int *i, t_my_env *myenv)
{
    int start = *i + 1; // start after '$'
    int var_len = 0;
    char *var_name;
    char *var_value = NULL;
    int env_idx;

    // Find variable name length (alphanumeric + underscore)
    while (input[start + var_len] && (isalnum((unsigned char)input[start + var_len]) || input[start + var_len] == '_'))
        var_len++;

    var_name = strndup(input + start, var_len);
    if (!var_name)
        return strdup(""); // Return empty string on malloc failure

    // Move i forward past the variable name
    *i = start + var_len;

    // Search for var_name in myenv->env
    for (env_idx = 0; myenv->env[env_idx]; env_idx++)
    {
        if (!strncmp(myenv->env[env_idx], var_name, var_len) &&
            myenv->env[env_idx][var_len] == '=')
        {
            var_value = strdup(myenv->env[env_idx] + var_len + 1);
            break;
        }
    }

    free(var_name);
    if (!var_value)
        return strdup(""); // If not found, return empty string
    return var_value;
}
