/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 09:58:53 by pmihangy          #+#    #+#             */
/*   Updated: 2024/02/27 10:32:30 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_digits(int n)
{
	size_t	i;

	i = 0;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	insert(char *str_num, long int num, size_t digits)
{
	if (num == 0)
	{
		str_num[0] = '0';
		str_num[1] = '\0';
	}
	while (digits--)
	{
		*(str_num + digits) = num % 10 + 48;
		num /= 10;
	}
}

char	*ft_itoa(int n)
{
	char		*str_num;
	size_t		digits;
	long int	num;

	num = n;
	digits = count_digits(n);
	if (n < 0)
	{
		num *= -1;
		digits++;
	}
	if (num == 0)
		digits++;
	str_num = (char *)malloc(sizeof(char) * (digits + 1));
	if (NULL == str_num)
		return (NULL);
	*(str_num + digits) = 0;
	insert(str_num, num, digits);
	if (n < 0)
		*(str_num + 0) = '-';
	return (str_num);
}
