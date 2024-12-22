/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:40:19 by trarijam          #+#    #+#             */
/*   Updated: 2024/10/21 09:46:32 by traveloa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_path(char **env, char *path_name)
{
	int		i;
	char	*path;
	char	**tmp;

	i = 0;
	path = 0;
	while (env[i])
	{
		if (ft_strncmp(path_name, env[i], ft_strlen(path_name)) == 0)
			break ;
		i++;
	}
	tmp = ft_split(env[i], '=');
	if (tmp)
	{
		path = ft_strdup(tmp[1]);
		free_split(tmp);
	}
	return (path);
}

void	update(t_list *env_lst, char *path, char *name)
{
	t_list	*head;
	char	*tmp;

	tmp = ft_strjoin(name, "=");
	head = env_lst;
	if (path)
	{
		while (env_lst)
		{
			if (ft_strncmp(tmp, (char *)env_lst->content, ft_strlen(tmp)) == 0)
			{
				free(env_lst->content);
				env_lst->content = ft_strjoin(tmp, path);
				break ;
			}
			env_lst = env_lst->next;
		}
		if (env_lst == NULL)
			ft_lstadd_back(&head, ft_lstnew(ft_strjoin(tmp, path)));
	}
	free(tmp);
}

void	update_pwd(char ***env, char *old_pwd)
{
	t_list	*env_lst;
	t_list	*head;
	char	*pwd;

	env_lst = get_env_lst(*env);
	pwd = getcwd(NULL, 0);
	head = env_lst;
	update(env_lst, old_pwd, "OLDPWD");
	update(env_lst, pwd, "PWD");
	free(pwd);
	free_split(*env);
	*env = list_to_tab(head);
	free_env_lst(head);
}

int	change_dir(char *path, char ***env)
{
	char	*path_name;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	path_name = get_path(*env, path);
	if (!path_name)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(" not set\n", 2);
		free(cwd);
		return (1);
	}
	if (chdir(path_name) == -1)
	{
		perror("cd");
		free(path_name);
		free(cwd);
		return (1);
	}
	free(path_name);
	update_pwd(env, cwd);
	free(cwd);
	return (0);
}

int	mns_cd(char **cmd, char ***env)
{
	char	*cwd;

	if (cmd[1] && cmd[2])
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (1);
	}
	if (!cmd[1] || ft_strncmp(cmd[1], "~", 2) == 0)
		return (change_dir("HOME", env));
	else if (ft_strncmp(cmd[1], "-", 2) == 0)
		return (change_dir("OLDPWD", env));
	else
	{
		cwd = getcwd(NULL, 0);
		if (chdir(cmd[1]) == -1)
		{
			perror("cd");
			free(cwd);
			return (1);
		}
		update_pwd(env, cwd);
		free(cwd);
		return (0);
	}
}
