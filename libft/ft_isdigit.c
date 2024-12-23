/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:07:28 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/12/23 11:18:59 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	printf("D%dD\n", c);
	return ((c >= 48 && c <= 57));
}

// int main()
// {
// 	printf("%d\n", ft_isdigit('`'));
// 	printf("%d\n", ft_isdigit('1'));
// }