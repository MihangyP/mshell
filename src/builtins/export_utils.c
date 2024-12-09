#include <minishell.h>

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

char	*get_str(char *s, char *to_exp, char *key)
{
	char 	*str;

	if (!ft_strncmp(get_key(s), key, INT_MAX))
	{
		str = ft_strdup(to_exp);
		if (!str)
			return (NULL);
	}
	else
	{
		str = ft_strdup(s);
		if (!str)
			return (NULL);
	}
	return (str);
}

t_status	fill_env_text(char *s1, char *s2, t_lst *new_env)
{
	char	*text;

	text = get_str(s1, s2, get_key(s2));
	if (!text)
		return (FAIL);
	new_env->text = ft_strdup(text);
	if (!new_env->text)
		return (FAIL);
	new_env->next = malloc(sizeof(t_lst));
	if (!new_env->next)
		return (FAIL);
	return (SUCCESS);
}
