/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 20:43:23 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/08/22 15:28:32 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

// void	*ft_custom_memcpy(void *dest, unsigned char src, size_t n)
// {
// 	unsigned char		*d;
// 	// const unsigned char	s;
// 	size_t				i;

// 	d = (unsigned char *)dest;
// 	// s = src;
// 	i = 0;
// 	while (i < n)
// 	{
// 		d[i] = src;
// 		i++;
// 	}
// 	return (dest);
// }

// int main(void)
// {
//     char src[] = "Hello, World!";
//     char dest[50];

//     // Use ft_memcpy to copy the string
//     ft_memcpy(dest, src, strlen(src) + 1);

//     printf("Source: %s\n", src);
//     printf("Destination: %s\n", dest);

//     return 0;
// }