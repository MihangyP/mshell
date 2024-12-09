#include <minishell.h>

bool	syntax(char *str)
{
	int	i;

	if (str[0] != '_' && !ft_isalpha(str[0]))
		return (false);
	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

void	check_env(t_lst *tmp, t_lst **env)
{
	if (tmp == (*env))
		(*env) = tmp->next;
	if (tmp->next == tmp)
		(*env) = NULL;
}

t_lst	*get_tmp(t_lst *env, char *str)
{
	t_lst	*tmp;
	t_lst	*curr;

	tmp = NULL;
	curr = env;
	while (curr->next != env)
	{
		if (!ft_strncmp(str, get_key(curr->text), INT_MAX))
		{
			tmp = curr;
			break ;
		}
		curr = curr->next;
	}
	if (!ft_strncmp(str, get_key(curr->text), INT_MAX))
		tmp = curr;
	return (tmp);
}

t_status	unset(char *str, t_lst **env)
{
	t_lst	*tmp;

	if (!str || !(*str))
		return (FAIL);
	if (!syntax(str))
	{
		print_error("unset: invalid identifier\n");
		return (SUCCESS);
	}
	if (!exist_in_env(str, *env))
		return (FAIL);
	tmp = get_tmp(*env, str);
	tmp->prev->next = tmp->next;
	tmp->next->prev = tmp->prev;
	free(tmp->text);
	check_env(tmp, env);
	free(tmp);
	tmp = NULL;
	return (SUCCESS);
}

int	unset_minishell(char **str, t_lst **env)
{
	int	exit_code;
	int	i;

	exit_code = 0;
	i = 0;
	while (str[i])
	{
		if (!unset(str[i], env))
			exit_code = 1;
		i++;
	}
	return (exit_code);
}
