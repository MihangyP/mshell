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

bool	valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!str[0] || (str[0] != '_' && !ft_isalpha(str[0])))
		return (false);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

char	*get_key(char *str)
{
	char	*tmp;
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		++i;
	tmp = malloc((i + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		tmp[i] = str[i];
		++i;
	}
	tmp[i] = '\0';
	return (tmp);
}

bool	exist_in_env(char *key, t_lst *env)
{
	t_lst	*curr;
	char	*env_key;

	curr = env;
	while (curr->next != env)
	{
		env_key = get_key(curr->text);	
		if (!ft_strncmp(env_key, key, INT_MAX))
			return (true);
		curr = curr->next;
	}
	env_key = get_key(curr->text);	
	if (!ft_strncmp(env_key, key, INT_MAX))
		return (true);
	return (false);
}

t_status	update_env_export(char *str, t_lst  **env)
{
	t_lst	*new_env;


	*new = new_env;
	return (SUCCESS);	
}

#if 1
t_status	export(char *str, t_lst **env)
{
	char	*key = get_key(str);
	if (!key)
		return (FAIL);
	if (exist_in_env(key, *env))
	{
		if (!update_env_export(str, env))
			return (FAIL);
	}
	else
	{
		if (!lst_append(env, str))
			return (FAIL);
	}
	return (SUCCESS);
}
#endif

#if 0
bool	export(char *str, t_lst **env)
{
	int		pos;
	int		i;
	char	*value;

	pos = exist(str, (*env));
	value = ft_strdup(str);
	if (!value)
		return (false);
	if (pos >= 0)
	{
		i = 0;
		while (i < pos)
		{
			(*env) = (*env)->next;
			i++;
		}
		free((*env)->text);
		(*env)->text = value;
	}
	else if (pos == -1)
		if (!lst_append(env, value))
			return (false);
	return (true);
}
#endif

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
			print_error("export: invalid identifier\n");
			exit_code = 1;
		}
		else if (!export(str[i], env))
			return (print_error("malloc error\n"));
		i++;
	}
	return (exit_code);
}
