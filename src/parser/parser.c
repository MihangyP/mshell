/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irazafim <irazafim@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:59:16 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/11 14:26:34 by irazafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exist_in(char *line, int *i, t_minishell *data);

static int	dollar_point_interrogation(t_minishell *data, char **str)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_itoa(data->exit_code);
	if (!tmp)
		return (0);
	tmp2 = ft_strjoin(*str, tmp);
	free(tmp);
	free(*str);
	if (!tmp2)
		return (0);
	*str = tmp2;
	return (1);
}

int	add_char(char *c, char **str, t_minishell *data, int *index)
{
	char	char_to_str[2];
	char	*tmp2;
	int		i;

	i = 0;
	// if (c[i] == '$' && !data->sq && exist_in(c, &i, data))
	// 	return (1);
	char_to_str[0] = *c;
	char_to_str[1] = '\0';
	(*index)++;
	tmp2 = ft_strjoin(*str, char_to_str);
	free(*str);
	if (!tmp2)
		return (0);
	*str = tmp2;
	return (1);
}

char	*get_elem_env(t_lst *env, char *key)
{
	t_lst	*tmp;
	int		len;
	int		t;

	if (!key)
		return (NULL);
	tmp = env;
	len = len_list(tmp);
	t = ft_strlen(key);
	while (len--)
	{
		if (ft_strncmp(tmp->text, key, t) == 0)
		{
			len = 0;
			while (tmp->text[len])
				if (tmp->text[len++] == '=')
					break ;
			return (ft_strdup(&(tmp->text[len])));
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_dollar_word(char *line, int size)
{
	char	*dollar;
	int		i;

	dollar = malloc(sizeof(char) * size);
	if (!dollar)
		return (NULL);
	i = 0;
	while (line[++i] && i < size)
		dollar[i - 1] = line[i];
	dollar[i - 1] = '\0';
	return (dollar);
}

static int	in_env(t_minishell *data, char *line, int size, char **str)
{
	char	*tmp;
	char	*key;
	char	*value;

	key = get_dollar_word(line, size);
	value = get_elem_env(data->env, key);
	if (key)
		free(key);
	tmp = ft_strjoin(*str, value);
	if (value)
		free(value);
	free(*str);
	if (!tmp)
		return (0);
	*str = tmp;
	return (1);
}

static int	ft_search(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (0);
}

static int	end_word(char *str, char *env)
{
	int	i;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		++i;
	if (i == ft_search(env, '='))
		return (i);
	return (0);
}

// size_t	len_list(t_lst *list)
// {
// 	t_lst	*tmp;
// 	size_t	i;

// 	if ((list))
// 	{
// 		tmp = list;
// 		i = 1;
// 		while (tmp->next != list)
// 		{
// 			++i;
// 			tmp = tmp->next;
// 		}
// 		return (i);
// 	}
// 	return (0);
// }

int	exist_in(char *line, int *i, t_minishell *data)
{
	t_lst	*tmp;
	int		len;

	if (line[*i + 1] == '?' || line[*i + 1] == '$')
		return (2);
	tmp = data->env;
	len = len_list(tmp);
	while (len--)
	{
		if (ft_strncmp(tmp->text, &line[*i + 1], \
			end_word(&line[*i + 1], tmp->text)) == 0)
		{
			*i += ft_strlen(tmp->text) - \
				ft_strlen(ft_strchr(tmp->text, '=')) + 1;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	add_dollar(char *line, int *index, char **str, t_minishell *data)
{
	int		ctrl;
	int		n;

	n = *index;
	ctrl = exist_in(line, index, data);
	if (ctrl == 1)
		return (in_env(data, &line[n], *index - n, str));
	else if (ctrl == 2)
	{
		(*index) += 2;
		return (dollar_point_interrogation(data, str));
	}
	else
	{
		++(*index);
		while (line[*index] && \
			(ft_isalnum(line[*index]) || line[*index] == '_'))
			++(*index);
		return (1);
	}
}

void	quoting_choice(bool *dq, bool *sq, int *index, char c)
{
	if ((c == '\'' || c == '"') && !*sq && !*dq)
	{
		if (c == '\'' && !*dq)
			*sq = true;
		else if (c == '"' && !*sq)
			*dq = true;
		if (index)
			++(*index);
	}
	else if ((c == '\'' || c == '"'))
	{
		if (c == '\'' && !*dq && *sq)
			*sq = false;
		else if (c == '"' && !*sq && *dq)
			*dq = false;
		if (index)
			++(*index);
	}
}

t_status	expand_entry(t_minishell *mshell, char **entry)
{
	bool	dq;
	int		i;
	char	*str;

	i = 0;
	dq = false;
	mshell->sq = false;
	str = ft_strdup("");
	while ((*entry)[i])
	{
		quoting_choice(&dq, &mshell->sq, NULL, (*entry)[i]);
		if ((*entry)[i] && (*entry)[i + 1] && (*entry)[i] == '$' && \
			((*entry)[i + 1] != '\'' && (*entry)[i + 1] != '"') && \
			(ft_isalpha((*entry)[i + 1]) || (*entry)[i + 1] == '?' || \
			(*entry)[i + 1] == '_') && !mshell->sq && \
			!add_dollar((*entry), &i, &str, mshell))
			return (FAIL);
		if ((*entry)[i] && !add_char(&(*entry)[i], &str, mshell, &i))
			return (FAIL);
	}
	free(*entry);
	*entry = str;
	return (SUCCESS);
}

// t_status	expand_entry(t_minishell *mshell, char **entry)
// {
// 	char	*result;
// 	size_t	result_len;

// 	result = NULL;
// 	result_len = 0;
// 	if (!mshell || !entry || !*entry)
// 		return (FAIL);
// 	if (!process_input(mshell, *entry, &result, &result_len))
// 	{
// 		free(result);
// 		return (FAIL);
// 	}
// 	free(*entry);
// 	*entry = result;
// 	return (SUCCESS);
// }

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

t_status	check_token_error(t_minishell *mshell)
{
	char	*err_message;

	err_message = NULL;
	if (mshell->token && \
		(mshell->token->prev->id == PIPE || mshell->token->id == PIPE))
	{
		err_message = ft_strdup("Syntax error\n");
		if (!err_message)
			return (FAIL);
		mshell->exit_code = 2;
		write(2, err_message, ft_strlen(err_message));
		free_token(&mshell->token);
		return (FAIL);
	}
	return (SUCCESS);
}

t_status	parse_entry(t_minishell *mshell, char *entry)
{
	if (!expand_entry(mshell, &entry))
		free_and_exit(mshell, 1);
	if (!tokenize_entry(&mshell->token, entry))
		free_and_exit(mshell, 1);
	free(entry);
	if (!check_token_error(mshell))
		return (FAIL);
	if (mshell->token)
	{
		if (!parsing_tokens(mshell))
		{
			free_token(&mshell->token);
			free_cmd(&mshell->cmd);
			return (FAIL);
		}
	}
	return (SUCCESS);
}
