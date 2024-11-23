/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:55:23 by pmihangy          #+#    #+#             */
/*   Updated: 2024/02/23 15:33:28 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	write_nbr(long int nbr, int fd)
{
	if (nbr > 9)
	{
		write_nbr(nbr / 10, fd);
	}
	ft_putchar_fd((nbr % 10) + 48, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	long int	x;

	x = n;
	if (x < 0)
	{
		ft_putchar_fd('-', fd);
		x *= -1;
	}
	write_nbr(x, fd);
}
