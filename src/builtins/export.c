/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:33:03 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/12 10:16:17 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	export_no_args(t_lst *env)
{
	char	**arr;
	int		i;
	int		j;

	arr = lst_to_arr(env);
	if (!arr)
		return (false);
	sort_array(arr, len_list(env));
	i = 0;
	while (arr[i])
	{
		printf("declare -x ");
		j = 0;
		while (arr[i][j] && arr[i][j] != '=')
			printf("%c", arr[i][j++]);
		if (arr[i][j] && arr[i][j] == '=')
			printf("=\"%s\"\n", &arr[i][j + 1]);
		else
			printf("\n");
		i++;
	}
	free(arr);
	return (true);
}

t_status	update_env_export(char *str, t_lst **env)
{
	t_lst *new_env;
	t_lst *tmp;
	t_lst *curr;

	new_env = malloc(sizeof(t_lst));
	if (!new_env)
		return (FAIL);
	tmp = new_env;
	curr = *env;
	while (curr->next != *env) {
		if (!fill_env_text(curr->text, str, new_env))
			return (free(new_env), FAIL);
		new_env->next = malloc(sizeof(t_lst));
		if (!new_env->next)
			return (free(new_env), FAIL);
		new_env->next->prev = new_env;
		new_env = new_env->next;
		curr = curr->next;
	}
	if (!fill_env_text(curr->text, str, new_env))
		return (free(new_env), FAIL);
	new_env->next = tmp;
	tmp->prev = new_env;
	*env = tmp;
	return (SUCCESS);
}

t_status	export(char *str, t_lst **env)
{
	char	*key;

	key = get_key(str);
	if (!key)
		return (FAIL);
	if (!exist_in_env(key, *env))
	{
		if (!lst_append(env, str))
			return (FAIL);
	}
	else
	{
		if (ft_strchr(str, '='))
		{
			if (!update_env_export(str, env))
				return (FAIL);
		}
	}
	return (SUCCESS);
}

int	export_minishell(char **str, t_lst **env)
{
	int	exit_code;
	int	i;

	exit_code = 0;
	i = 1;
	if (!str || !str[i])
	{
		if (*env && !export_no_args((*env)))
			return (print_error("malloc error\n"));
		return (0);
	}
	while (str[i])
	{
		if (!valid_identifier(str[i]))
		{
			print_error("export: not a valid identifier\n");
			exit_code = 1;
		}
		else if (!export(str[i], env))
			return (print_error("malloc error\n"));
		i++;
	}
	return (exit_code);
}
