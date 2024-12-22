/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 08:11:34 by traveloa          #+#    #+#             */
/*   Updated: 2024/10/21 07:30:45 by traveloa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>

int	ft_pwd(char **args, char **env)
{
	char	*pwd;

	(void)args;
	(void)env;
	pwd = NULL;
	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, 1);
	if (pwd)
		free(pwd);
	return (EXIT_SUCCESS);
}
