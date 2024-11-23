/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:32:44 by pmihangy          #+#    #+#             */
/*   Updated: 2024/06/09 15:39:56 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	convert(char *str, va_list ap)
{
	char	specifier;
	int		nbr_chars;

	nbr_chars = 0;
	specifier = *(++str);
	if (specifier == 'c')
		ft_putchar(va_arg(ap, int), &nbr_chars);
	else if (specifier == 's')
		nbr_chars += print_str(va_arg(ap, char *));
	else if (specifier == 'p')
		nbr_chars += put_p(va_arg(ap, unsigned long long));
	else if (specifier == 'd' || specifier == 'i')
		nbr_chars += print_nbr(va_arg(ap, int));
	else if (specifier == 'u')
		nbr_chars += put_u(va_arg(ap, long));
	else if (specifier == '%')
		ft_putchar('%', &nbr_chars);
	else if (specifier == 'x' || specifier == 'X')
		print_in_hex(va_arg(ap, unsigned int), specifier, &nbr_chars);
	return (nbr_chars);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		nbr_chars;

	va_start(ap, format);
	nbr_chars = 0;
	while (*format)
	{
		if (*format == '%')
		{
			nbr_chars += convert((char *)format, ap);
			format += 2;
		}
		else
		{
			ft_putchar_fd(*format, 1);
			format++;
			nbr_chars++;
		}
	}
	va_end(ap);
	return (nbr_chars);
}
