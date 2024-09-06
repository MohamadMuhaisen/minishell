/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 23:09:35 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/06/10 17:11:24 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy_forward(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*d;
	const char	*s;

	d = (char *)dest;
	s = (const char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

void	*ft_memcpy_backward(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*d;
	const char	*s;

	d = (char *)dest;
	s = (const char *)src;
	i = n;
	while (i > 0)
	{
		d[i - 1] = s[i - 1];
		i--;
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest == src || n == 0)
	{
		return (dest);
	}
	if (dest > src)
	{
		return (ft_memcpy_backward(dest, src, n));
	}
	else
	{
		return (ft_memcpy_forward(dest, src, n));
	}
}

// int main(void)
// {
// 	char src[50] = "Hello, World!";
// 	char dest[50];

// 	ft_memmove(dest, src, strlen(src) + 1);

// 	printf("Source: %s\n", src);
// 	printf("Destination: %s\n", dest);

// 	ft_memmove(src + 7, src, strlen("Hello") + 1);
// 	printf("Overlapping move: %s\n", src);

// 	return 0;
// }