#include <minishell.h>

t_status	expand_entry(t_minishell *mshell, char **entry)
{
    char 	*input;
    char 	*result;
    size_t 	result_len;
    bool 	in_single_quote;
	bool	in_double_quote;

    if (!mshell || !entry || !*entry)
        return (FAIL);
    input = *entry;
    result = NULL;
    result_len = 0;
    in_single_quote = false;
	in_double_quote = false;
    while (*input) {
        if (*input == '\'' && !in_double_quote)
		{
            in_single_quote = !in_single_quote;
            result = str_append(result, "'", &result_len);
            input++;
        }
		else if (*input == '"' && !in_single_quote)
		{
            in_double_quote = !in_double_quote;
            result = str_append(result, "\"", &result_len);
            input++;
        }
		else if (*input == '$' && !in_single_quote)
		{
            input++;
            char var_name[256] = {0};
            size_t var_len = 0;
            if (*input == '?' || ft_isdigit(*input))
                var_name[var_len++] = *input++;
			else
			{
				while (ft_isalpha(*input) || *input == '_')
                    var_name[var_len++] = *input++;
            }
            if (!get_var(mshell, &result, var_name, &result_len))
			{
                free(result);
                return (FAIL);
            }
        }
		else
		{
            char temp[2] = {*input, '\0'};
            result = str_append(result, temp, &result_len);
            if (!result)
                return (FAIL);
            input++;
        }
    }
    free(*entry);
    *entry = result;
    return (SUCCESS);
}

t_status	tokenize_entry(t_token **root, char *entry)
{
	while (*entry)
	{
		while (is_space(*entry))
			++entry;
		if (*entry && !is_operator(*entry))
		{
			if (!insert_cmd_arg(root, &entry))
			{
				if (root)
					free_token(root);
				return (FAIL);
			}
		}
		else if (*entry && is_operator(*entry))
		{
			if (!insert_operator(root, &entry))
			{
				if (root)
					free_token(root);
				return (FAIL);
			}
		}
	}
	return (SUCCESS);
}

t_status	parse_entry(t_minishell *mshell, char *entry)
{
	char	*err_message;

	if (!expand_entry(mshell, &entry))
		return (FAIL);
	if (!tokenize_entry(&mshell->token, entry))
		return (FAIL);
	if (mshell->token && mshell->token->prev->id == PIPE)
	{
		err_message = ft_strdup("Syntax error\n");
		if (!err_message)
			return (false);
		write(2, err_message, ft_strlen(err_message));
		mshell->exit_code = 2;
		free_token(&mshell->token);
		return (false);
	}
	if (mshell->token)
	{
		if (!parsing_tokens(mshell))
		{
			free_token(&mshell->token);
			free_cmd(&mshell->cmd);
			return (false);
		}
	}
	return (SUCCESS);
}
