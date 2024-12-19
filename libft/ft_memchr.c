/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 23:44:01 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/06/10 17:11:24 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;
	unsigned char		uc;
	size_t				i;

	p = (const unsigned char *)s;
	uc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (p[i] == uc)
		{
			return ((void *)(p + i));
		}
		i++;
	}
	return (NULL);
}

// int main(void)
// {
//     const char buffer[] = "Hello, World!";
//     char *result;

//     result = ft_memchr(buffer, 'W', sizeof(buffer));
//     if (result)
//     {
//         printf("Character 'W' found at position: %ld\n", result - buffer);
//     }
//     else
//     {
//         printf("Character 'W' not found\n");
//     }

//     result = ft_memchr(buffer, 'x', sizeof(buffer));
//     if (result)
//     {
//         printf("Character 'x' found at position: %ld\n", result - buffer);
//     }
//     else
//     {
//         printf("Character 'x' not found\n");
//     }

//     return 0;
// }