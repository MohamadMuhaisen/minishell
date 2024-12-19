/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 00:04:38 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/06/11 16:49:54 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (i < n)
	{
		*(char *)(s + i) = (unsigned char)c;
		i++;
	}
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	total_size;

	total_size = nmemb * size;
	if (size != 0 && nmemb > 2147483647 / size)
		return (0);
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, total_size);
	return (ptr);
}

// int main(void)
// {
//     size_t nmemb = 5;
//     size_t size = sizeof(int);
//     int *array = (int *)ft_calloc(nmemb, size);

//     if (array)
//     {
//         for (size_t i = 0; i < nmemb; i++)
//         {
//             printf("array[%zu] = %d\n", i, array[i]);
//         }
//         free(array);
//     }
//     else
//     {
//         printf("Memory allocation failed\n");
//     }
//     return 0;
// }