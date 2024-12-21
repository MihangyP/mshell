/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:48:25 by trarijam          #+#    #+#             */
/*   Updated: 2024/12/15 20:25:37 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_value(int value)
{
	static int	val;

	if (value == -1)
		return (val);
	val = value;
	return (value);
}

void	set_variable(int value)
{
	handle_value(value);
}

int	get_variable(void)
{
	return (handle_value(-1));
}