#include <minishell.h>

char	*get_env_value(t_minishell *mshell, const char *key)
{
	t_lst	*curr;
	size_t	entry_key_len;

	if (!mshell || !mshell->env || !key)
		return (NULL);
	curr = mshell->env;
	while (curr->next != mshell->env)
	{
		if (!curr->text)
			continue ;
		if (ft_strchr(curr->text, '='))
		{
			entry_key_len = ft_strchr(curr->text, '=') - curr->text;
			if (entry_key_len == ft_strlen(key) && !ft_strncmp(curr->text, key, ft_strlen(key)))
				return (ft_strchr(curr->text, '=') + 1);
		}
		curr = curr->next;
	}
	if (ft_strchr(curr->text, '='))
	{
		entry_key_len = ft_strchr(curr->text, '=') - curr->text;
		if (entry_key_len == ft_strlen(key) && !ft_strncmp(curr->text, key, ft_strlen(key)))
			return (ft_strchr(curr->text, '=') + 1);
	}
   return (NULL);
}

char	*str_append(char *dest, const char *src, size_t *dest_len)
{
    size_t	src_len;
    char	*new_str;

    src_len = ft_strlen(src);
	new_str = malloc(*dest_len + src_len + 1);
    if (!new_str)
		return (NULL);
    if (dest)
	{
        ft_memcpy(new_str, dest, *dest_len);
        free(dest);
    }
  	ft_memcpy(new_str + *dest_len, src, src_len + 1);
    *dest_len += src_len;
    return (new_str);
}

t_status	get_var(t_minishell *mshell, char **res, char *name, size_t *len)
{
	char	*exit_code_str;
	char	*value;

    if (!ft_strncmp(name, "?", 1))
	{
        exit_code_str = ft_itoa(mshell->exit_code);
        if (!exit_code_str)
            return (FAIL);
        *res = str_append(*res, exit_code_str, len);
        free(exit_code_str);
        if (!*res)
            return (FAIL);
    }
	else
	{
        value = get_env_value(mshell, name);
        if (value)
            *res = str_append(*res, value, len);
		else 
            *res = str_append(*res, "", len);
        if (!*res)
            return (FAIL);
    }
    return (SUCCESS);
}
