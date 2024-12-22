/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:37:47 by trarijam          #+#    #+#             */
/*   Updated: 2024/08/22 15:23:56 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	lst_len;

	if (!lst)
		return (0);
	lst_len = 0;
	while (lst)
	{
		lst = lst->next;
		lst_len++;
	}
	return (lst_len);
}
