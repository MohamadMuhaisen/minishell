/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:39:13 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/09/11 03:02:54 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = (char *)malloc(len1 + len2 + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, len1);
	ft_memcpy(str + len1, s2, len2);
	str[len1 + len2] = '\0';
	return (str);
}

// char	*ft_custom_strjoin(char const *s1, char s2)
// {
// 	int		len1;
// 	int		len2;
// 	char	*str;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	len1 = ft_strlen(s1);
// 	len2 = 1;
// 	str = (char *)malloc(len1 + len2 + 1);
// 	if (!str)
// 		return (NULL);
// 	ft_memcpy(str, s1, len1);
// 	ft_custom_memcpy(str + len1, s2, len2);
// 	str[len1 + len2] = '\0';
// 	return (str);
// }

// int main(void)
// {
//     char const *s1 = "Hello,";
//     char const *s2 = " World!";
//     char *substr;

//     substr = ft_strjoin(s1, s2);
//     if (substr)
//     {
//         printf("joined str: %s\n", substr);
//         free(substr);
//     }
//     else
//     {
//         printf("Memory allocation failed\n");
//     }

//     return 0;
// }