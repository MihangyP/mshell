/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 07:54:36 by traveloa          #+#    #+#             */
/*   Updated: 2024/09/28 10:19:53 by traveloa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	concatenate_var(t_list *env_lst, char *tmp, char *var_value
			, char *var_name)
{
	while (env_lst)
	{
		tmp = get_var_name((char *)env_lst->content);
		if (ft_strncmp(var_name, tmp, ft_strlen(var_name)) == 0)
		{
			free(tmp);
			tmp = (char *)env_lst->content;
			env_lst->content = ft_strjoin(tmp, var_value);
			free(tmp);
			return (1);
		}
		free(tmp);
		env_lst = env_lst->next;
	}
	return (0);
}

void	handle_var_concatenation(t_list *env_lst, char *var_name
			, char *var_value)
{
	char	*tmp;
	t_list	*head;

	head = env_lst;
	tmp = NULL;
	if (concatenate_var(env_lst, tmp, var_value, var_name) == 0)
	{
		tmp = ft_strjoin(var_name, "=");
		free(var_name);
		var_name = ft_strjoin(tmp, var_value);
		ft_lstadd_back(&head, ft_lstnew((void *)ft_strdup(var_name)));
		free(tmp);
	}
}

void	add_new_var(t_list *env_lst, char *var)
{
	char	*var_name;
	char	*var_value;

	var_name = get_var_name(var);
	if (ft_strchr(var, '+') != NULL)
	{
		var_value = get_var_value(var);
		handle_var_concatenation(env_lst, var_name, var_value);
		free(var_value);
	}
	else if (ft_strchr(var, '='))
	{
		remove_one(&env_lst, var_name);
		ft_lstadd_back(&env_lst, ft_lstnew((void *)ft_strdup(var)));
	}
	else
	{
		if (lst_srch_var(env_lst, var_name) == 0)
			ft_lstadd_back(&env_lst, ft_lstnew((void *)ft_strdup(var)));
	}
	free(var_name);
}

void	export_assignement(char **assignement, t_list *env_lst, int	*status)
{
	int		j;

	j = 1;
	while (assignement && assignement[j])
	{
		if (check_var_name(assignement[j]) == 0)
		{
			ft_putstr_fd(assignement[j], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			*status = EXIT_FAILURE;
			j++;
			continue ;
		}
		add_new_var(env_lst, assignement[j]);
		j++;
	}
}

int	ft_export(char **cmd, char ***env)
{
	t_list	*env_lst;
	char	**tmp;
	int		status;

	tmp = *env;
	status = 0;
	env_lst = get_env_lst(*env);
	if (!cmd[1])
		print_export(env_lst);
	else
	{
		export_assignement(cmd, env_lst, &status);
		free_split(tmp);
		*env = list_to_tab(env_lst);
	}
	free_env_lst(env_lst);
	return (status);
}
