/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:06:11 by trarijam          #+#    #+#             */
/*   Updated: 2024/10/31 07:48:00 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_var_name_length(char *str)
{
	int		i;

	i = 0;
	if (ft_isdigit(str[i]))
		return (1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

char	*get_env_value(char *var, char **env)
{
	int		i;
	int		var_len;

	i = 0;
	var_len = ft_strlen(var);
	while (env[i])
	{
		if (ft_strncmp(env[i], var, var_len) == 0
			&& env[i][var_len] == '=')
			return (env[i] + var_len + 1);
		i++;
	}
	return (NULL);
}

char	*str_append(char *str, char *append)
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

char	*expand_env_var(char *var_name, char **env)
{
	int		var_len;
	char	*var;
	char	*value;

	var_len = get_var_name_length(var_name);
	var = (char *)malloc(sizeof(char) * (var_len + 1));
	ft_strlcpy(var, var_name, (var_len + 1));
	value = get_env_value(var, env);
	free(var);
	if (value == NULL)
		return (NULL);
	return (value);
}
