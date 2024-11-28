#include <minishell.h>

t_lst	*new_lst_element(char *str)
{
	t_lst	*new;

	new = malloc(sizeof(t_lst));
	if (!new)
		return (NULL);
	new->text = ft_strdup(str);
	if (new->text == NULL)
		return (NULL);
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_status	lst_append(t_lst **env, char *str)
{
	t_lst	*new;
	
	new = new_lst_element(str);	
	if (new == NULL)
		return (FAIL);
	if (*env == NULL)
	{
		*env = new;
		(*env)->prev = *env;
		(*env)->next = *env;
	}
	new->prev = (*env)->prev;
	new->next = (*env);
	(*env)->prev->next = new;
	(*env)->prev = new;
	return (SUCCESS);
}

size_t	len_list(t_lst *list)
{
	t_lst	*tmp;
	size_t	i;

	if ((list))
	{
		tmp = list;
		i = 1;
		while (tmp->next != list)
		{
			++i;
			tmp = tmp->next;
		}
		return (i);
	}
	return (0);
}

char	**lst_to_arr(t_lst *env)
{
	t_lst	*lst;
	char	**dest;
	int		i;

	dest = NULL;
	i = 0;
	lst = env;
	dest = (char **)malloc(sizeof(char *) * (len_list(lst) + 1));
	if (!dest)
		return (NULL);
	dest[i] = (lst->text);
	lst = lst->next;
	i++;
	while (lst != env)
	{
		dest[i] = (lst->text);
		lst = lst->next;
		i++;
	}
	dest[i] = NULL;
	return (dest);
}
