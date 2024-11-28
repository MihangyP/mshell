#include <minishell.h>

int	ft_strslashjoin(char *dest, char *str, char *env, int *index)
{
	int			i;
	int			j;

	i = 0;
	while (*index < (PATH_MAX - 1) && env[(*index)] && env[(*index)] != ':')
		dest[i++] = env[(*index)++];
	++(*index);
	dest[i++] = '/';
	j = 0;
	while (j < (PATH_MAX - 1) && str[j])
		dest[i++] = str[j++];
	dest[i] = '\0';
	return (0);
}

char	*cmd_not_found(char *sample)
{
	write(2, sample, ft_strlen(sample));
	write(2, " : command not found\n", 21);
	return (NULL);
}

char	*create_paths(t_lst *env, int len)
{
	t_lst	*tmp;

	tmp = env;
	while (len--)
	{
		if (ft_strncmp(tmp->text, "PATH=", 5) == 0)
			return (&(tmp->text[5]));
		tmp = tmp->next;
	}
	return (NULL);
}

char	*find_cmd(t_minishell *mshell, char *sample, t_lst *env)
{
	char		*paths;
	char		path[PATH_MAX];
	int			i;
	int			len;

	paths = create_paths(env, len_list(env));
	if (!paths || ft_strlen(sample) > PATH_MAX / 2)
		return (cmd_not_found(sample));
	i = 0;
	len = ft_strlen(paths);
	while (i < len)
	{
		ft_strslashjoin(path, sample, paths, &i);
		if (access(path, F_OK) == 0)
		{
			sample = ft_strdup(path);
			if (!sample)
			{
				print_error("Malloc error");
				mshell->exit_code = -1;
			}
			return (sample);
		}
	}
	return (cmd_not_found(sample));
}
