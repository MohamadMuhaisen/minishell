/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 23:14:41 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/06/10 17:11:24 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;
	size_t				i;

	p1 = (const unsigned char *)s1;
	p2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
		i++;
	}
	return (0);
}

// int main(void)
// {
//     char str1[] = "Hello, World!";
//     char str2[] = "Hello, World!";
//     char str3[] = "Hello, world!";
//     int result;
//     result = ft_memcmp(str1, str2, strlen(str1));
//     if (result == 0)
//     {
//         printf("str1 and str2 are equal\n");
//     }
//     else
//     {
//         printf("str1 and str2 are not equal\n");
//     }
//     result = ft_memcmp(str1, str3, strlen(str1));
//     if (result == 0)
//     {
//         printf("str1 and str3 are equal\n");
//     }
//     else
//     {
//         printf("str1 and str3 are not equal\n");
//     }
//     return 0;
// }