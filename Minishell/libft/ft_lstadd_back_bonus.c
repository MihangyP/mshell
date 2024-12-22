/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 08:55:08 by trarijam          #+#    #+#             */
/*   Updated: 2024/08/22 15:23:49 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lastlst;

	if (!(*lst))
		*lst = new;
	else if (lst && new)
	{
		lastlst = ft_lstlast(*lst);
		lastlst->next = new;
	}
}
