/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 23:23:26 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/06/10 17:11:24 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *target, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*target == '\0')
		return ((char *)str);
	while (i < len && str[i])
	{
		if (str[i] == target[0])
		{
			j = 0;
			while (target[j] && (i + j) < len)
			{
				if (str[i + j] != target[j])
					break ;
				j++;
			}
			if (target[j] == '\0')
				return ((char *)&str[i]);
		}
		i++;
	}
	return (NULL);
}

// int main()
// {
// 	char *str = "hello this is a test";
// 	printf("%s\n",ft_strnstr(str,"is",40));
// }