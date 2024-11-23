
int	len_text(char *str)
{
	int	len;

	len = 0;
	while (str[len] && !is_operator(str[len]) && !is_space(str[len]) && !is_quote(str[len]))
		++len;
	return (len);
}

//$HOME /
//echo $HOME "hello $USER" 'ddfjf $PATH'
// TODO: verify if the text is in env
//^
int	line_expanded_len(char *str)
{
	int	len;
	int	i;
	char	quote;
	char	*text;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			quote = str[i];
			++i;
			while (str[i] != quote)
			{
				if (quote == '\'' || str[i] != '$')
				{
					++len;
					++i;
				}
				else
				{
					text = ft_substr(str, i + 1, len_text(str + i + 1));
					if (!text)
						error("Cannot substract the string\n");
					text = getenv(text);
					len += ft_strlen(text);
					i += len_text(str + i);
				}
			}
			len += 2;
			++i;
		}
		else
		{
			if (str[i] != '$')
			{
				++len;
				++i;
			}
			else
			{
				text = ft_substr(str, i + 1, len_text(str + i + 1));
				if (!text)
					error("Cannot substract the string\n");
				text = getenv(text);
				len += ft_strlen(text);
				i += len_text(str + i);
			}
		}
	}
	return (len);
}

void	expand(char **line)
{
	char	*str;
	char	*tmp;
	char	*text;
	int		i;
	int		j;
	int		str_size;
	char	quote;

	tmp = *line;
	str_size = line_expanded_len(tmp);
	str = malloc((str_size + 1) * sizeof(char));
	if (!str)
		error("malloc error");
	i = 0;
	j = 0;
	while (tmp[i])
	{
		if (tmp[i] == '\"' || tmp[i] == '\'')
		{
			quote = tmp[i];
			++i;
			str[j] = quote;
			++j;
			while (tmp[i] != quote)
			{
				if (quote == '\'' || tmp[i] != '$')
				{
					str[j] = tmp[i];
					++j;
					++i;
				}
				else
				{
					text = ft_substr(tmp, i + 1, len_text(tmp + i + 1));
					if (!text)
						error("Cannot substract the string\n");
					text = getenv(text);
					ft_memcpy(str + j, text, ft_strlen(text));
					j += ft_strlen(text);
					i += len_text(tmp + i);
				}
			}
			str[j] = quote;
			++j;
			++i;
		}
		else
		{
			if (tmp[i] != '$')
			{
				str[j] = tmp[i];
				++j;
				++i;
			}
			else
			{
				text = ft_substr(tmp, i + 1, len_text(tmp + i + 1));
				if (!text)
					error("Cannot substract the string\n");
				text = getenv(text);
				ft_memcpy(str + j, text, ft_strlen(text));
				j += ft_strlen(text);
				i += len_text(tmp + i);
			}
		}
	}
	str[j] = '\0';
	*line = str;
}
