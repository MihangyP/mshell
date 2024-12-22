/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irazafim <irazafim@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:59:16 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/22 15:38:48 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*char_append(char *str, char c);

void	my_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

t_status	expand_entry(t_minishell *mshell, char **entry)
{
	char	*result;
	size_t	result_len;

	result = NULL;
	result_len = 0;
	if (!mshell || !entry || !*entry)
		return (FAIL);
	if (!process_input(mshell, *entry, &result, &result_len))
	{
		free(result);
		return (FAIL);
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
				if (*root)
					free_token(root);
				return (FAIL);
			}
		}
		else if (*entry && is_operator(*entry))
		{
			if (!insert_operator(root, &entry))
			{
				if (*root)
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

bool	read_in_stdin(t_minishell *mshell, int fd, char *word)
{
	char	*buf;

	while (true)
	{
		buf = NULL;
		buf = readline("> ");
		if (!buf && read_in_stdin_error(word))
			break ;
		if (!ft_strncmp(word, buf, INT_MAX) || g_pid == -42)
			break ;
		if (!expand_entry(mshell, &buf))
			free_and_exit(mshell, 1);
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		free(buf);
	}
	return (free(buf), close(fd), true);
}

int	wait_process(void)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	wait(&status);
	signal(SIGINT, handle_sigint);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 130)
			return (130);
		else
			return (WEXITSTATUS(status));
	}
	return (0);
}

void	handler_sigint_heredoc(int signum)
{
	g_pid = signum;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

void	setup_signals_heredoc(void)
{
	signal(SIGINT, handler_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

#if 1
int	get_var_name_length(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]))
		return (1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

char	*get_value(char *var, t_lst *env)
{
	int		var_len;
	t_lst	*curr;

	var_len = ft_strlen(var);
	curr = env;
	while (curr->next != env)
	{
		if (ft_strncmp(curr->text, var, var_len) == 0 && env->text[var_len] == '=')
			return (curr->text + var_len + 1);
		curr = curr->next;
	}
	if (ft_strncmp(curr->text, var, var_len) == 0 && env->text[var_len] == '=')
		return (curr->text + var_len + 1);
	return (NULL);
}

char	*expand_env_var(char *var_name, t_lst *env)
{
	int		var_len;
	char	*var;
	char	*value;

	var_len = get_var_name_length(var_name);
	var = (char *)malloc(sizeof(char) * (var_len + 1));
	ft_strlcpy(var, var_name, (var_len + 1));
	value = get_value(var, env);
	free(var);
	if (var == NULL)
		return (NULL);
	return (value);
}

char	*expand_special_char(char *str, t_minishell *mshell, int *i)
{
	char	*result;
	char	*var_value;

	result = NULL;
	var_value = NULL;
	if (str[*i + 1] == '?')
	{
		result = ft_itoa(mshell->exit_code);
		(*i)++;
	}
	else
	{
		var_value = expand_env_var(str + *i + 1, mshell->env);
		result = (char *)malloc(sizeof(char) * (ft_strlen(var_value) + 3));
		result[0] = '"';
		ft_strlcpy(result + 1, var_value, ft_strlen(var_value) + 1);
		result[ft_strlen(var_value) + 1] = '"';
		*i += get_var_name_length(str + *i + 1);
	}
	return (result);
}

char	*str_append2(char *str, char *append)
{
	char	*result;
	int		len1;
	int		len2;

	len1 = 0;
	if (str != NULL)
		len1 = ft_strlen(str);
	len2 = ft_strlen(append);
	result = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (str)
		ft_strlcpy(result, str, (len1 + 1));
	ft_strlcpy(result + len1, append, len2 + 1);
	free(str);
	return (result);
}

char	*special_expand_char(char *str, t_minishell *mshell)
{
	char	*result;
	char	*tmp;
	int		i;

	i = -1;
	tmp = NULL;
	result = NULL;
	while (str[++i])
	{
		if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '?'))
		{
			tmp = expand_special_char(str, mshell, &i);
			result = str_append2(result, tmp);
			free(tmp);
		}
		else
			result = char_append(result, str[i]);
	}
	return (result);
}

char	*get_result(char *line, int is_expand, t_minishell *mshell)
{
	char	*result;

	result = NULL;
	if (line != NULL && is_expand == 0)
		result = special_expand_char(line, mshell);
	else
		result = ft_strdup(line);
	return (result);
}

int	init_heredoc(char **line, int fd)
{
	*line = readline("> ");
	if (*line == NULL)
	{
		if (g_pid)
		{
			close(fd);
			return (-1);
		}
		close(fd);
		return (-2);
	}
	return (1);
}

// TODO: to check
int	is_delimiter(const char *line, const char *heredoc_delimiter)
{
	if (line == NULL)
		return (1);
	if (ft_strncmp(line, heredoc_delimiter, ft_strlen(heredoc_delimiter) + 1) == 0)
		return (1);
	return (0);
}

int	check_delimiter(char *heredoc_delimiter, char *result, char *line)
{
	if (is_delimiter(heredoc_delimiter, result))
	{
		free(line);
		if (result != NULL)
			free(result);
		return (1);
	}
	return (0);
}

int	process_heredoc_redir(t_heredoc ms_heredoc, t_minishell *mshell)
{
	char	*line;
	char	*result;

	line = NULL;
	result = NULL;
	while (1 && ms_heredoc.fd > 0)
	{
		if (init_heredoc(&line, ms_heredoc.fd) < 0)
		{
			if (g_pid == SIGINT)
				return (130);
			return (166);
		}
		result = get_result(line, ms_heredoc.is_expand, mshell);
		if (check_delimiter(ms_heredoc.tmp_value, result, line))
			break ;
		my_putendl_fd(result, ms_heredoc.fd);
		free(line);
		free(result);
	}
	close(ms_heredoc.fd);
	return (1);
}
#endif

int	is_invalid_redirection(t_token	*token)
{
	return (token == NULL);
}

char	*char_append(char *str, char c)
{
	char	*result;
	int		len;

	len = 0;
	if (str != NULL)
		len = ft_strlen(str);
	result = (char *)malloc(sizeof(char) * (len + 2));
	if (str)
		ft_strlcpy(result, str, (len + 1));
	result[len] = c;
	result[len + 1] = '\0';
	free(str);
	return (result);
}

char	*expand_for_heredoc(char *heredoc_delimiter)
{
	char	*result;
	int		i;

	result = NULL;
	i = 0;
	while (heredoc_delimiter[i] != '\0')
	{
		if (heredoc_delimiter[i] == '\'' || heredoc_delimiter[i] == '"')
			i++;
		else if (heredoc_delimiter[i] == '$' && (heredoc_delimiter[i + 1] == '\'' || heredoc_delimiter[i + 1] == '"'))
			i++;
		else
		{
			result = char_append(result, heredoc_delimiter[i]);
			i++;
		}
	}
	if (result == NULL)
		return (ft_strdup(""));
	return (result);
}

int	mns_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	determine_expansion(t_token *curr, char *tmp)
{
	if (mns_strcmp(curr->text, tmp) == 0)
		return (0);
	return (1);
}

char	*get_name_file(int in_pipe)
{
	char	*nb;
	char	*name;

	nb = NULL;
	nb = ft_itoa(in_pipe);
	name = ft_strjoin(".tmp", nb);
	free(nb);
	return (name);
}

int	process_heredoc_token(t_token **curr, t_minishell *mshell, int in_pipe)
{
	char		*name;
	int			status;
	t_heredoc	ms_heredoc;
	
	name = NULL;
	ms_heredoc.tmp_value = NULL;
	*curr = (*curr)->next;
	if (is_invalid_redirection(*curr))
		return (-2);
	ms_heredoc.tmp_value = expand_for_heredoc((*curr)->text);
	ms_heredoc.is_expand = determine_expansion(*curr, ms_heredoc.tmp_value);
	name = get_name_file(in_pipe);
	ms_heredoc.fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	status = process_heredoc_redir(ms_heredoc, mshell);
	free(name);
	free(ms_heredoc.tmp_value);
	return (status);
}

int	process_tokens_heredoc(t_token *token, t_minishell *mshell)
{
	static int	in_pipe;
	int			status;
	t_token		*curr;

	in_pipe = 0;
	status = 0;
	curr = token;
	/*print_token(curr);*/
	if (curr->id == PIPE)
		in_pipe += 1;
	if (curr->id == HEREDOC)
		status = process_heredoc_token(&curr, mshell, in_pipe);
	curr = curr->next;
	while (curr != token)
	{
		if (curr->id == PIPE)
			in_pipe += 1;
		if (curr->id == HEREDOC)
			status = process_heredoc_token(&curr, mshell, in_pipe);
		if (status == -2)
			break ;
		curr = curr->next;
	}
	return (status);
}

void	handle_child_process(t_minishell *mshell, char *entry)
{
	int		status;

	g_pid = 0;
	setup_signals_heredoc();
	status = 1;
	tokenize_entry(&mshell->token, entry);
	/*if (!token)*/
		/*exit(status);*/
	status = process_tokens_heredoc(mshell->token, mshell);
	free_token(&mshell->token);
	mshell->token = NULL;
	exit(status);
}

int	heredoc(t_minishell *mshell, char *entry)
{
	pid_t	pid_child;

	pid_child = fork();
	if (pid_child == -1)
	{
		perror("fork");
		free_and_exit(mshell, 2);
	}
	else if (pid_child == 0)
		handle_child_process(mshell, entry);
	else
		return (wait_process());
	return (0);
}

void	close_tmp(void)
{
	char	*name;
	char	*nb;
	int		i;

	i = 0;
	while (1)
	{
		nb = ft_itoa(i);
		name = ft_strjoin(".tmp", nb);
		if (unlink(name) == -1)
		{
			free(nb);
			free(name);
			break ;
		}
		free(nb);
		free(name);
		i++;
	}
}

int	handle_state(int state)
{
	if (state == 130)
	{
		close_tmp();
		return (1);
	}
	else if (state == 166)
	{
		close_tmp();
		return (2);
	}
	return (0);
}

t_status	parse_entry(t_minishell *mshell, char *entry)
{
	int	state;

	state = heredoc(mshell, entry);
	if (handle_state(state) == 1)
		return (FAIL);
	else if (handle_state(state) == 2)
		return (FAIL);
	if (g_pid == 130)
		mshell->exit_code = 130;
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
