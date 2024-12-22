/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:06:43 by trarijam          #+#    #+#             */
/*   Updated: 2024/08/22 15:59:14 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	verify_n(int n)
{
	if (n <= 0)
		return (1);
	return (0);
}

static int	after_malloc(char *str, int n)
{
	if (n < 0)
	{
		str[0] = '-';
		return (-n);
	}
	return (n);
}

char	*ft_itoa(int n)
{
	int		len;
	int		tmp;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = verify_n(n);
	tmp = n;
	while (tmp)
	{
		tmp /= 10;
		len++;
	}
	str = (char *)ft_calloc(len + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	n = after_malloc(str, n);
	str[len] = '\0';
	while (len-- && str[len] != '-')
	{
		str[len] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}
