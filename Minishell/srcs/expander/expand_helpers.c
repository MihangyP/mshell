/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:12:59 by trarijam          #+#    #+#             */
/*   Updated: 2024/12/17 18:31:59 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_quotes(char c, int *in_single_quotes, int *in_double_quotes)
{
	if (c == '\'' && !(*in_double_quotes))
		*in_single_quotes = !(*in_single_quotes);
	else if (c == '"' && !(*in_single_quotes))
		*in_double_quotes = !(*in_double_quotes);
}

char	*expand_special_char(char *str, char **env, int *i, int exit_status)
{
	char	*result;
	char	*var_value;

	result = NULL;
	var_value = NULL;
	if (str[*i + 1] == '?')
	{
		result = ft_itoa(exit_status);
		(*i)++;
	}
	else
	{
		var_value = expand_env_var(str + *i + 1, env);
		result = (char *)malloc(sizeof(char) * (ft_strlen(var_value) + 3));
		result[0] = '"';
		ft_strlcpy(result + 1, var_value, ft_strlen(var_value) + 1);
		result[ft_strlen(var_value) + 1] = '"';
		printf("result: %s\n", result);
		*i += get_var_name_length(str + *i + 1);
	}
	return (result);
}

int	should_expand(char *str, int i, int in_single_quotes)
{
	return (str[i] == '$' && !in_single_quotes
		&& (ft_isalnum(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '?'));
}


char	*remove_quotes(char *str)
{
	int		in_d_quotes;
	int		in_s_quotes;
	char	*result;
	int		i;

	result = NULL;
	i = 0;
	in_d_quotes = 0;
	in_s_quotes = 0;
	while (str[i] != '\0')
	{
		if ( handle_quotes_expander(str[i], &in_s_quotes, &in_d_quotes))
		{
			
		}
		else
		{
			if (is_ignored_dollar(str[i], str[i + 1], in_d_quotes,
				in_s_quotes) == 1)
				result = char_append(result, str[i]);
		}
		i++;
	}
	return (result);
}
