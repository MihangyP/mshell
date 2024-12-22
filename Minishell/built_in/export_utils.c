/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 08:03:02 by traveloa          #+#    #+#             */
/*   Updated: 2024/09/26 10:34:10 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_var_name(char *name)
{
	int	i;

	i = 0;
	if (ft_isalpha(name[i]) == 0 && name[i] != '_')
		return (0);
	i++;
	while (name[i])
	{
		if (name[i] == '=')
			break ;
		if (name[i] == '_')
			i++;
		if (ft_isalnum(name[i]) == 0)
		{
			if (name[i] == '+' && name[i + 1] == '=')
				i++;
			else
				return (0);
		}
		i++;
	}
	return (1);
}

char	*get_var_name(char *var)
{
	int		i;
	int		j;
	char	*name;

	i = 0;
	j = 0;
	while (var[i] && var[i] != '+' && var[i] != '=')
		i++;
	name = ft_calloc(i + 1, sizeof(char));
	while (j < i)
	{
		name[j] = var[j];
		j++;
	}
	name[j] = '\0';
	return (name);
}

char	*get_var_value(char *var)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (var[i] == '\0')
		return (0);
	i++;
	value = ft_calloc(ft_strlen(var) - i + 1, sizeof(char));
	while (var[i])
	{
		value[j] = var[i];
		i++;
		j++;
	}
	return (value);
}

void	print_var_value(char *value, int i, t_list *env_lst)
{
	ft_putchar_fd(value[i], 1);
	i++;
	ft_putchar_fd('"', 1);
	ft_putstr_fd((char *)env_lst->content + i, 1);
	ft_putchar_fd('"', 1);
}

void	print_export(t_list *env_lst)
{
	int		i;
	char	*tmp;

	sort_env_lst(&env_lst);
	while (env_lst)
	{
		i = 0;
		tmp = (char *)env_lst->content;
		ft_putstr_fd("declare -x ", 1);
		while (tmp[i] != '=' && tmp[i])
		{
			ft_putchar_fd(tmp[i], 1);
			i++;
		}
		if (tmp[i])
			print_var_value(tmp, i, env_lst);
		ft_putstr_fd("\n", 1);
		env_lst = env_lst->next;
	}
	free_env_lst(env_lst);
}
