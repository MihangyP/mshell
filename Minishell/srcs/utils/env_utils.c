/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 07:57:31 by traveloa          #+#    #+#             */
/*   Updated: 2024/10/22 09:06:59 by traveloa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*get_env_lst(char **envp)
{
	int		i;
	t_list	*env_lst;

	i = 0;
	env_lst = ft_lstnew((void *)ft_strdup(envp[i]));
	i++;
	while (envp[i])
	{
		ft_lstadd_back(&env_lst, ft_lstnew((void *)ft_strdup(envp[i])));
		i++;
	}
	return (env_lst);
}

void	sort_env_lst(t_list	**env_lst)
{
	t_list	*env_tmp;
	char	*tmp;

	env_tmp = *env_lst;
	while (env_tmp->next)
	{
		if (mns_strcmp((char *)env_tmp->content,
				(char *)env_tmp->next->content) > 0)
		{
			tmp = (char *)env_tmp->content;
			env_tmp->content = env_tmp->next->content;
			env_tmp->next->content = tmp;
			env_tmp = *env_lst;
		}
		else
			env_tmp = env_tmp->next;
	}
}

char	**list_to_tab(t_list *env_lst)
{
	int		size;
	char	**env;
	int		i;

	i = 0;
	size = ft_lstsize(env_lst);
	env = malloc(sizeof(char *) * (size + 1));
	while (env_lst)
	{
		env[i] = ft_strdup((char *)env_lst->content);
		i++;
		env_lst = env_lst->next;
	}
	env[i] = NULL;
	return (env);
}

char	**cpy_env(char **env)
{
	int		i;
	char	**env_cpy;

	i = 0;
	while (env[i])
		i++;
	env_cpy = malloc(sizeof(char *) *(i + 1));
	i = 0;
	while (env[i])
	{
		env_cpy[i] = ft_strdup(env[i]);
		i++;
	}
	env_cpy[i] = NULL;
	return (env_cpy);
}

void	mns_close_fds(int fd1, int fd2)
{
	close (fd1);
	close (fd2);
}
