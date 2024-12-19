/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:12:59 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/06/11 20:55:18 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_number_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len += 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

void	convert_to_string(char *str, long num, int len)
{
	int	is_negative;

	is_negative = 0;
	if (num < 0)
	{
		is_negative = 1;
		num = -num;
	}
	str[len] = '\0';
	while (len-- > 0)
	{
		if (is_negative && len == 0)
		{
			str[len] = '-';
			break ;
		}
		str[len] = num % 10 + '0';
		num /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	num;

	num = n;
	len = ft_number_len(num);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	convert_to_string(str, num, len);
	return (str);
}

// int main(void)
// {
// 	printf("%s\n", ft_itoa(-2147483648));
// }