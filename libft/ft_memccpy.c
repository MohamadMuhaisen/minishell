/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 20:52:48 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/06/10 17:11:24 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	unsigned char		uc;
	size_t				i;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	uc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		if (s[i] == uc)
		{
			return ((void *)(d + i + 1));
		}
		i++;
	}
	return (NULL);
}

// int main(void)
// {
//     const char src[] = "Hello, World!";
//     char dest[50];
//     char *result;
//     // Use ft_memccpy to copy until character ',' is encountered
//     result = ft_memccpy(dest, src, ',', sizeof(src));
//     if (result)
//     {
//         printf("Character ',' found. Copied until: %s\n", dest);
//     }
//     else
//     {
//         printf("Character ',' not found. Full copy: %s\n", dest);
//     }
//     return 0;
// }