/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:01:15 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/06/11 13:26:52 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

// int main(void) {
//     char *str;

//     str = (char *)malloc(6 * sizeof(char));
//     if (str == NULL)
// 		return (1);
//     str[0] = 'h';
//     str[1] = 'e';
//     str[2] = 'l';
//     str[3] = 'l';
//     str[4] = 'o';
//     str[5] = '\0';
//     printf("Original string: %s\n", str);
//     ft_bzero(str, 6 * sizeof(char));
//     printf("Modified string: %s\n", str);
// }
