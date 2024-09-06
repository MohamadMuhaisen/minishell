/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:54:46 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/06/10 17:11:24 by mmuhaise         ###   ########.fr       */
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

// int main(void)
// {
//     char arr[5];
//     int i;

//     arr[0] = 'h';
//     arr[1] = 'e';
//     arr[2] = 'l';
//     arr[3] = 'l';
//     arr[4] = 'o';

//     ft_memset(arr + 1, '.', 2);

//     for (i = 0; i < 5; i++)
//     {
//         printf("%c", arr[i]);
//     }
//     printf("\n");

//     return 0;
// }