/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:17:50 by traveloa          #+#    #+#             */
/*   Updated: 2024/10/21 10:07:06 by traveloa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_exit_status(unsigned int *status, char **cmd, char *str)
{
	int	i;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i += 1;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			ft_putstr_fd(cmd[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			*status = 2;
			break ;
		}
		i++;
	}
}

static int	check_digit(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

static void	exit_n_free(char **envp, t_ast_node *ast, int status)
{
	free_ast(&ast);
	free_split(envp);
	exit(status);
}

int	ft_exit(char **cmd, t_ast_node *ast, char **envp, int flag)
{
	unsigned int	status;
	char			*str;

	status = 0;
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (cmd[1] && cmd[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		if (check_digit(cmd[1]) == 1)
			return (EXIT_FAILURE);
		else
			exit_n_free(envp, ast, 2);
	}
	else if (cmd[1])
	{
		str = ft_strtrim(cmd[1], " ");
		status = ft_atoi(str);
		get_exit_status(&status, cmd, str);
		free(str);
	}
	if (flag == 1)
		exit_n_free(envp, ast, status);
	return (status);
}
