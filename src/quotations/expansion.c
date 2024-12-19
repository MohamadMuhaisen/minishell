/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:56:33 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/09 08:15:59 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_for_i(char *tofind, char **var_and_val, t_my_env *my_env)
{
	if (*tofind == '?')
	{
		free(*var_and_val);
		*var_and_val = ft_itoa(my_env->exit_status);
	}
}

void	get_var(t_my_env *myenv, char *tofind,
			t_ll_node **lst)
{
	int		i;
	char	*var_and_val;

	var_and_val = NULL;
	i = -1;
	while (myenv->env[++i])
	{
		if (!strncmp(myenv->env[i], tofind, ft_strlen(tofind)))
			var_and_val = ft_strdup(myenv->env[i]);
	}
	check_for_i(tofind, &var_and_val, myenv);
	if (!var_and_val)
		return ;
	i = 0;
	while (var_and_val[i] && var_and_val[i] != '=')
		i++;
	i++;
	change_i_helper(&i, tofind);
	while (var_and_val[i])
	{
		add_to_str(var_and_val[i], lst);
		i++;
	}
	free(var_and_val);
}

int	check_if_solo_dollar(t_ll_node **lst, char *str, int *j)
{
	if (!str[*j + 1] || str[*j + 1] == ' '
		|| str[*j + 1] == '"' || str[*j + 1] == '\'')
	{
		add_to_str('$', lst);
		(*j)++;
		return (1);
	}
	return (0);
}

int	prepare_var_search(t_ll_node **lst, char *str, int *j)
{
	if (str[*j + 1] == '$')
	{
		handle_double_dollar(lst);
		*j += 2;
		return (1);
	}
	if (check_if_solo_dollar(lst, str, j))
		return (1);
	return (0);
}

void	search_and_add_var(t_ll_node **lst, char *str,
			int *j, t_my_env *myenv)
{
	int		i;
	char	*to_find;
	char	*tmp;

	if (prepare_var_search(lst, str, j))
		return ;
	(*j)++;
	i = 0;
	if ((str[*j] == '?'))
		i = 1;
	else
	{
		while (str[*j + i] && str[*j + i] != '$'
			&& str[*j + i] != '\'' && str[*j + i] != '"'
			&& str[*j + i] != ' ' && str[*j + i] != ']')
			i++;
	}
	to_find = ft_substr(str, *j, i);
	tmp = to_find;
	to_find = ft_strjoin(to_find, "=");
	free(tmp);
	get_var(myenv, to_find, lst);
	(*j) += i;
	free(to_find);
}
