#include <minishell.h>

void	copy_token(char *entry, int length, char *str, int i)
{
	int	j;

	j = 0;
	while (entry[i + j] && i < length)
	{
		if (entry[i + j] == '\'' && ++j)
		{
			while (entry[i + j] != '\'' && ++i)
				str[i - 1] = entry[(i - 1) + j];
			j++;
		}
		else if (entry[i + j] == '"' && ++j)
		{
			while (entry[i + j] != '"' && ++i)
				str[i - 1] = entry[(i - 1) + j];
			j++;
		}
		else
		{
			str[i] = entry[i + j];
			i++;
		}
	}
	str[i] = 0;
}

int	cmd_arg_len(char *entry, int *quotes)
{
	int	i;

	i = 0;
	*quotes = 0;
	while (entry[i] && !is_space(entry[i]) && !is_operator(entry[i]))
	{
		if (entry[i] == '"' || entry[i] == '\'')
		{
			(*quotes)++;
			if (entry[i++] == '"')
				while (entry[i] && entry[i] != '"')
					++i;
			else
				while (entry[i] && entry[i] != '\'')
					++i;
			if (entry[i])
				++i;
		}
		if (entry[i] && entry[i] != '"' && entry[i] != '\'' && \
			!is_space(entry[i]) && !is_operator(entry[i]))
			++i;
	}
	return (i);
}

t_status	insert_cmd_arg(t_token **root, char **entry)
{
	char	*str;
	int		len;
	int		quotes;
	int		i;

	i = 0;
	len = cmd_arg_len(*entry, &quotes);
	if (((len) - (2 * quotes)) < 0)
		return (SUCCESS);
	str = malloc(sizeof(char) * ((len + 1) - (2 * quotes)));
	if (!str)
		return (FAIL);
	copy_token(*entry, len - (2 * quotes), str, i);
	if (!append_token(root, str, 0))
		return (FAIL);
	if ((*root)->prev == (*root) || (*root)->prev->prev->id == PIPE)
		(*root)->prev->id = CMD;
	else
		(*root)->prev->id = ARG;
	(*entry) += len;
	return (SUCCESS);
}

t_status	insert_operator(t_token **root, char **entry)
{
	if (**entry == '<')
	{
		if (*(*entry + 1) == '<')
		{
			if (!append_token(root, ft_strdup("<<"), HEREDOC))	
				return (FAIL);
			(*entry) += 2;
		}
		else
		{
			if (!append_token(root, ft_strdup("<"), INPUT))
				return (FAIL);
			(*entry)++;
		}
	}
	else if (**entry == '>')
	{
		if (*(*entry + 1) == '>')
		{
			if (!append_token(root, ft_strdup(">>"), APPEND))	
				return (FAIL);
			(*entry) += 2;
		}
		else
		{
			if (!append_token(root, ft_strdup(">"), TRUNC))
				return (FAIL);
			(*entry)++;
		}
	}
	else
	{
		if (!append_token(root, ft_strdup("|"), PIPE))
			return (FAIL);
		(*entry)++;
	}
	return (SUCCESS);
}
