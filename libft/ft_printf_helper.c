/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 23:51:37 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/07/10 20:24:01 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_hex_lower(unsigned int nbr, t_format *format)
{
	return (ft_putnbr_hex(nbr, "0123456789abcdef", format, 1));
}

int	ft_putnbr_hex_upper(unsigned int nbr, t_format *format)
{
	return (ft_putnbr_hex(nbr, "0123456789ABCDEF", format, 1));
}

int	parse_int(va_list ap, t_format *format)
{
	int	count;

	count = handle_output(ap, format);
	format->field_width -= count;
	if (format->left_justify)
		left_justify(format, &count, 0);
	return (count);
}

void	add_zeros_unsigned(t_format *format, unsigned long int *n, int *count,
				int base)
{
	unsigned int	copy;
	int				len;

	len = 0;
	copy = *n;
	while (copy)
	{
		copy /= base;
		len++;
	}
	if (*n == 0)
		format->field_width--;
	format->field_width -= len;
	while (format->field_width > 0)
	{
		*count += write(1, "0", 1);
		format->field_width--;
	}
}
