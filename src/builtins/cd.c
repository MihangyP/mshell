/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irazafim <irazafim@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:32:33 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/23 14:47:19 by irazafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_lst *my_lstnew(char *content)
{
    t_lst *new_node;

    new_node = malloc(sizeof(t_lst));
    if (!new_node)
        return (NULL);
    new_node->text = content;
    new_node->next = new_node;
    new_node->prev = new_node;
    return (new_node);
}

void my_lstadd_back(t_lst **lst, t_lst *new_node)
{
    t_lst *tail;

    if (!lst || !new_node)
        return;

    if (!*lst)
    {
        *lst = new_node;
        return;
    }
    tail = (*lst)->prev;
    tail->next = new_node;
    new_node->prev = tail;
    new_node->next = *lst;
    (*lst)->prev = new_node;
}


char *get_path(t_lst *env, char *path_name)
{
    t_lst *current;
    size_t path_name_len;

    if (!env || !path_name)
        return (NULL);

    current = env;
    path_name_len = ft_strlen(path_name);

    while (1)
    {
        if (ft_strncmp(path_name, current->text, path_name_len) == 0 && current->text[path_name_len] == '=')
            return (ft_strdup(&current->text[path_name_len + 1]));
        current = current->next;
        if (current == env)
            break;
    }
    return (NULL);
}

void update(t_lst **env_lst, char *path, char *name)
{
    t_lst *current;
    char *tmp;

    if (!env_lst || !*env_lst || !name)
        return;

    tmp = ft_strjoin(name, "=");
    current = *env_lst;

    if (path)
    {
        while (1)
        {
            if (ft_strncmp(tmp, (char *)current->text, ft_strlen(tmp)) == 0)
            {
                free(current->text);
                current->text = ft_strjoin(tmp, path);
                free(tmp);
                return;
            }
            current = current->next;
            if (current == *env_lst)
                break;
        }
        my_lstadd_back(env_lst, my_lstnew(ft_strjoin(tmp, path)));
    }
    free(tmp);
}

void update_pwd(t_lst **env, char *oldpwd)
{
    t_lst *new_env;
    t_lst *current;
    t_lst *new_node;
    char *pwd;

    if (!env || !*env)
        return;
    pwd = getcwd(NULL, 0);
    new_env = NULL;
    current = *env;
    while (1)
    {
        new_node = malloc(sizeof(t_lst));
        if (!new_node)
        {
            free_env(&new_env);
            free(pwd);
            return;
        }
        new_node->text = ft_strdup(current->text);
        new_node->next = NULL;
        new_node->prev = NULL;
        if (!new_env)
        {
            new_env = new_node;
            new_env->next = new_env;
            new_env->prev = new_env;
        }
        else
        {
            new_node->next = new_env;
            new_node->prev = new_env->prev;
            new_env->prev->next = new_node;
            new_env->prev = new_node;
        }
        current = current->next;
        if (current == *env)
            break;
    }
    update(&new_env, oldpwd, "OLDPWD");
    update(&new_env, pwd, "PWD");
    free_env(env);
    *env = new_env;
    free(pwd);
}

int	change_dir(char *path, t_minishell *mshell)
{
	char	*path_name;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	path_name = get_path(mshell->env, path);
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
	update_pwd(&mshell->env, cwd);
	free(cwd);
	return (0);
}

int cd_minishell(t_minishell *mshell, char **params)
{
	char	*cwd;

	if (params[1] && params[2])
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (1);
	}
	if (!params[1] || ft_strncmp(params[1], "~", 2) == 0)
		return (change_dir("HOME", mshell));
	else if (ft_strncmp(params[1], "-", 2) == 0)
		return (change_dir("OLDPWD", mshell));
	else
	{
		cwd = getcwd(NULL, 0);
		if (chdir(params[1]) == -1)
		{
			perror("cd");
			free(cwd);
			return (1);
		}
		update_pwd(&mshell->env, cwd);
		free(cwd);
		return (0);
	}
}