/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:32:26 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/07/10 20:23:36 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init_format(t_format *format)
{
	format->left_justify = 0;
	format->zero_pad = 0;
	format->precision = -1;
	format->alternate_form = 0;
	format->space = 0;
	format->plus = 0;
	format->field_width = 0;
}

void	fill_format(const char **str, t_format *format)
{
	while (**str == '-' || **str == '0' || **str == '.' || **str == '#'
		|| **str == ' ' || **str == '+')
	{
		if (**str == '-')
			format->left_justify = 1;
		else if (**str == '0')
			format->zero_pad = 1;
		else if (**str == '.')
			format->precision = 1;
		else if (**str == '#')
			format->alternate_form = 1;
		else if (**str == ' ')
			format->space = 1;
		else if (**str == '+')
			format->plus = 1;
		(*str)++;
	}
	if (**str >= '0' && **str <= '9')
	{
		format->field_width = ft_atoi(*str);
		while (**str >= '0' && **str <= '9')
			(*str)++;
	}
}

void	left_justify(t_format *format, int *count, int limit)
{
	while (format->field_width > limit)
	{
		*count += write(1, " ", 1);
		format->field_width--;
	}
}

int	parse_arg(const char **str, va_list ap)
{
	int			count;
	t_format	format;

	count = 0;
	init_format(&format);
	(*str)++;
	fill_format(str, &format);
	if (**str == 'c')
		count += parse_c(ap, &format);
	else if (**str == 's')
		count += parse_s(ap, &format);
	else if (**str == 'p')
		count += ft_putptr_fd(va_arg(ap, void *), &format, 0);
	else if (**str == 'd' || **str == 'i')
		count += parse_int(ap, &format);
	else if (**str == 'u')
		count += ft_putnbr_unsigned(va_arg(ap, unsigned int), 1, &format);
	else if (**str == 'x')
		count += ft_putnbr_hex_lower(va_arg(ap, unsigned int), &format);
	else if (**str == 'X')
		count += ft_putnbr_hex_upper(va_arg(ap, unsigned int), &format);
	else if (**str == '%')
		count += write(1, "%", 1);
	return (count);
}

int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	ap;

	count = 0;
	va_start(ap, str);
	while (*str)
	{
		if (*str == '%')
			count += parse_arg(&str, ap);
		else
			count += write(1, str, 1);
		str++;
	}
	va_end(ap);
	return (count);
}

// int	main(void)
// {
// 	int printed_chars;
// 	int *ptr = NULL;

// 	printed_chars = ft_printf("[%-3d]\n", 1);
// 	printf("[%-3d]\n", 1);
// 	printf("D%dD\n", printed_chars);
// }

// 	printf("Printed characters: %d\n", printed_chars);
// 	printed_chars = ft_printf("Pointer address: %p\n", NULL);
// 	printf("Printed characters: %d\n", printed_chars);
// 	printed_chars = ft_printf("number: %d\n", 42);
// 	printf("Printed characters: %d\n", printed_chars);
// 	printed_chars = ft_printf("number: %i\n", 42);
// 	printf("Printed characters: %d\n", printed_chars);
// 	printed_chars = ft_printf("Unsigned number: %u\n", -1);
// 	printf("Printed characters: %d\n", printed_chars);
// 	printed_chars = ft_printf("Percentage sign: %%\n");
// 	printf("Printed characters: %d\n", printed_chars);
// 	printed_chars = ft_printf("Hexadecimal (lowercase): %x\n", 255);
// 	printf("Printed characters: %d\n", printed_chars);
// 	printed_chars = ft_printf("Hexadecimal (uppercase): %X\n", 255);
// 	printf("Printed characters: %d\n", printed_chars);
// }
