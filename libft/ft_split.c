/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:10:41 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/06/11 13:14:26 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_words(char const *s, char c)
{
	int	i;
	int	count;
	int	word_flag;

	i = 0;
	count = 0;
	word_flag = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i])
		{
			word_flag = 1;
			i++;
		}
		if (word_flag)
			count++;
		word_flag = 0;
	}
	return (count);
}

int	ft_word_len(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	*ft_get_word(const char *str, int len)
{
	char	*word;
	int		i;

	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

char	**populate_split_array(char const *s, char c, char **strs)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		len = ft_word_len(s + i, c);
		if (len)
		{
			strs[j] = ft_get_word(s + i, len);
			j++;
		}
		i += len;
	}
	strs[j] = NULL;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		word_count;

	word_count = ft_count_words(s, c);
	strs = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!s)
		return (NULL);
	if (!strs)
		return (NULL);
	if (!populate_split_array(s, c, strs))
		return (NULL);
	return (strs);
}

// int	main(void)
// {
// 	char	*s = ",,,Hello,,,,,World,Test,,,";
// 	int		i;
// 	char	**strs;

// 	strs = ft_split(s, ',');
// 	if (strs)
// 	{
// 		for (i = 0; strs[i] != NULL; i++)
// 		{
// 			printf("strs[%d] = %s\n", i, strs[i]);
// 			free(strs[i]);
// 		}
// 		free(strs);
// 	}
// 	return (0);
// }
