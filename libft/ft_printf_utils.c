/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:38:21 by pmihangy          #+#    #+#             */
/*   Updated: 2024/06/09 15:39:40 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_u_nbr(unsigned int n, int fd, int *nbr_chars)
{
	if (n > 9)
	{
		(*nbr_chars)++;
		ft_put_u_nbr(n / 10, fd, nbr_chars);
	}
	ft_putchar_fd((n % 10) + 48, fd);
}

void	print_in_hex(unsigned long nbr, char c, int *nbr_chars)
{
	char	numbers[32];
	int		i;

	i = 0;
	if (0 == nbr)
		ft_putchar('0', nbr_chars);
	while (nbr)
	{
		if (nbr % 16 < 10)
			numbers[i] = (nbr % 16) + 48;
		else
		{
			if (c == 'x')
				numbers[i] = (nbr % 16) + 87;
			else
				numbers[i] = (nbr % 16) + 55;
		}
		nbr /= 16;
		i++;
	}
	while (--i >= 0)
		ft_putchar(numbers[i], nbr_chars);
}

int	put_u(long nbr)
{
	int				nbr_chars;
	unsigned int	u_nbr;

	nbr_chars = 0;
	u_nbr = (unsigned int)nbr;
	ft_put_u_nbr(u_nbr, 1, &nbr_chars);
	return (++nbr_chars);
}
