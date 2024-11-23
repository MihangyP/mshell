/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 08:55:24 by pmihangy          #+#    #+#             */
/*   Updated: 2024/10/17 14:01:11 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_islower(int c)
{
	if (c > 96 && c < 123)
		return (1);
	return (0);
}

static int	ft_isupper(int c)
{
	if (c > 64 && c < 91)
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	return (ft_islower(c) || ft_isupper(c));
}
