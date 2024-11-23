/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:29:29 by pmihangy          #+#    #+#             */
/*   Updated: 2024/06/09 15:39:19 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(char c, int *nbr_chars)
{
	ft_putchar_fd(c, 1);
	(*nbr_chars)++;
}

int	print_str(char *s)
{
	int	nbr_chars;

	nbr_chars = 0;
	if (NULL == s)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	ft_putstr_fd(s, 1);
	nbr_chars += ft_strlen(s);
	return (nbr_chars);
}

int	print_nbr(int nbr)
{
	int		nbr_chars;
	char	*s;

	nbr_chars = 0;
	s = ft_itoa(nbr);
	ft_putnbr_fd(nbr, 1);
	nbr_chars += ft_strlen(s);
	free(s);
	return (nbr_chars);
}

int	put_p(unsigned long long n)
{
	int	nbr_chars;

	if (0 == n)
	{
		ft_putstr_fd("(nil)", 1);
		nbr_chars = 5;
	}
	else
	{
		ft_putstr_fd("0x", 1);
		nbr_chars = 2;
		print_in_hex(n, 'x', &nbr_chars);
	}
	return (nbr_chars);
}
