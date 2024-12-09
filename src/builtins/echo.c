/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:32:39 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/09 14:32:41 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	has_dash_n_option(char *str)
{
	int	i;

	i = 0;
	if (str[i] && str[i] == '-')
	{
		++i;
		while (str[i] && str[i] == 'n')
			i++;
		if (i == (int)ft_strlen(str))
			return (true);
	}
	return (false);
}

int	echo_minishell(char **av)
{
	int		ac;
	int		i;
	bool	dash_n_option;

	ac = 0;
	i = 1;
	dash_n_option = false;
	while (av[ac])
		++ac;
	while (av[i] && has_dash_n_option(av[i]))
	{
		dash_n_option = true;
		++i;
	}
	while (i < ac)
	{
		printf("%s", av[i]);
		if (i != ac - 1)
			printf(" ");
		++i;
	}
	if (!dash_n_option)
		printf("\n");
	return (0);
}
