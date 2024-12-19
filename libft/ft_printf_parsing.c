/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:37:38 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/07/10 20:23:54 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	parse_c(va_list ap, t_format *format)
{
	int	count;

	count = write(1, &(char){va_arg(ap, int)}, 1);
	if (format->left_justify)
	{
		left_justify(format, &count, 1);
	}
	return (count);
}

void	add_zeros(t_format *format, int *n, int *count)
{
	int	copy;
	int	len;

	len = 0;
	copy = *n;
	while (copy)
	{
		copy /= 10;
		len++;
	}
	if (*n <= 0)
	{
		format->field_width--;
		if (*n < 0 && *n != -2147483648)
		{
			*count += write(1, "-", 1);
			*n *= -1;
		}
	}
	format->field_width -= len;
	while (format->field_width > 0)
	{
		*count += write(1, "0", 1);
		format->field_width--;
	}
}

int	handle_output(va_list ap, t_format *format)
{
	int	count;
	int	n;

	count = 0;
	n = va_arg(ap, int);
	if (format->plus == 1 && n >= 0)
		count += write(1, "+", 1);
	if (format->space && n >= 0)
		count += write(1, " ", 1);
	if (format->zero_pad)
		add_zeros(format, &n, &count);
	if (n == 0)
	{
		count++;
		write(1, "0", 1);
	}
	else
	{
		if (n < 0)
			count++;
		ft_putnbr_fd(n, 1);
		while (n != 0 && ++count)
			n /= 10;
	}
	return (count);
}

int	parse_s(va_list ap, t_format *format)
{
	int		count;
	char	*str;
	int		len;
	int		padding;

	count = 0;
	str = va_arg(ap, char *);
	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (format->precision >= 0 && format->precision < len)
		len = format->precision;
	if (format->field_width > len)
		padding = format->field_width - len;
	else
		padding = 0;
	if (!format->left_justify)
		while (padding-- > 0)
			count += write(1, " ", 1);
	count += write(1, str, len);
	if (format->left_justify)
		while (padding-- > 0)
			count += write(1, " ", 1);
	return (count);
}
