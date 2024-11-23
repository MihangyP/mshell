/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:54:38 by pmihangy          #+#    #+#             */
/*   Updated: 2024/02/25 10:41:47 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **list, void (*del)(void*))
{
	t_list	*curr;
	t_list	*tmp;

	if (list && del)
	{
		curr = *list;
		while (curr)
		{
			tmp = curr;
			curr = curr->next;
			del(tmp->content);
			free(tmp);
		}
		*list = NULL;
	}
}
