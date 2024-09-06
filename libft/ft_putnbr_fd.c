/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:26:55 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/06/12 13:30:24 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nblong;

	nblong = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		nblong *= -1;
	}
	if (nblong / 10)
	{
		ft_putnbr_fd(nblong / 10, fd);
	}
	ft_putchar_fd(nblong % 10 + '0', fd);
}
