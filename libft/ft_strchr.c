/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 20:36:05 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/06/11 18:13:59 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
		{
			return ((char *)s);
		}
		s++;
	}
	if (!(char)c)
		return ((char *)s);
	return (NULL);
}

// int main(void)
// {
// 	char buffer1[40] = "computer program";
// 	char * ptr;
// 	int	ch = 'p';

// 	ptr = ft_strchr(buffer1, 0);
// 	printf("%s\n", buffer1 + strlen(buffer1));
// 	if(ptr == buffer1 + strlen(buffer1))
// 		printf("BLA\n");
// 	printf( "The first occurrence of %c in '%s' is '%s'\n",
//             ch, buffer1, ptr );
// }