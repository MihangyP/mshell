/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:32:33 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/22 15:34:17 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	update_pwd(mshell, cwd);
	free(cwd);
	return (0);
}

int	cd_minishell(t_minishell *mshell, char **params)
{
	int		arg_len;
	char	*cwd;

	arg_len = count_arg(params);
	if (params[1] && params[2])
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (1);
	}
	if (!params[1] || ft_strncmp(params[1], "~", 2) == 0)
		return (change_dir("HOME", mshell));
	else if (ft_strncmp(cmd[1], "-", 2) == 0)
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
		update_pwd(mshell, cwd);
		free(cwd);
		return (0);
	}
	/*int		res;*/
	/*int		arg_len;*/
	/*char	oldpwd[PATH_MAX];*/
	/*char	pwd[PATH_MAX];*/
	/*char	*path;*/

	/*arg_len = count_arg(params);*/
	/*if (arg_len == 1 || arg_len == 2)*/
	/*{*/
		/*if (arg_len == 1)*/
			/*path = getpath(mshell->env, "HOME=");*/
		/*else*/
			/*path = params[1];*/
		/*if (!getcwd(oldpwd, PATH_MAX))*/
			/*free_and_exit(mshell, 1);*/
		/*res = chdir(path);*/
		/*if (res == -1)*/
			/*return (perror(path), 1);*/
		/*if (!getcwd(pwd, PATH_MAX))*/
			/*free_and_exit(mshell, 1);*/
		/*if (!update_env(mshell, oldpwd, pwd))*/
			/*free_and_exit(mshell, 1);*/
		/*return (res);*/
	/*}*/
	/*return (print_cd_error(params[0]), 1);*/
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

#if 0

static int	count_arg(char **params)
{
	int	count;

	count = 0;
	while (params[count])
		count++;
	return (count);
}

static void	error_malloc(void)
{
	print_error(ERR_MALLOC);
	return ;
}

static void	update_oldpwd(t_data *data)
{
	t_list	*tmp;
	char	*test;
	int		len;

	tmp = data->env;
	test = NULL;
	len = len_list(tmp);
	while (len--)
	{
		if (ft_strncmp(tmp->str, "PWD=", 3) == 0)
			test = tmp->str;
		tmp = tmp->next;
	}
	if (!test)
		export("OLDPWD", &data->env);
	if (test)
	{
		test = ft_strjoin("OLD", test);
		if (!test)
			return (error_malloc());
		export(test, &data->env);
	}
	free(test);
}

static void	update_pwd(t_data *data, char *param)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	update_oldpwd(data);
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		perror(param);
		return ;
	}
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		return (error_malloc());
	export(pwd, &data->env);
	free(pwd);
}

int	ft_cd(t_data *data, char **params)
{
	int	res;

	if (count_arg(params) == 2)
	{
		res = chdir(params[1]);
		if (res == 0)
			update_pwd(data, params[1]);
		if (res == -1)
			res *= -1;
		if (res == 1)
			perror(params[1]);
		return (res);
	}
	return (1);
}

#if 0

static int	count_arg(char **params)
{
	int	count;

	count = 0;
	while (params[count])
		count++;
	return (count);
}

bool	pwd_exist(char *str, t_lst *env)
{
	t_lst	*curr;

	curr = env;
	if (!ft_strncmp(curr->text, str, ft_strlen(str)))
		return (true);
	curr = curr->next;
	while (curr)
	{
		if (!ft_strncmp(curr->text, str, ft_strlen(str)))
			return (true);
		curr = curr->next;
	}
	return (false);
}

static char	*get_text(t_minishell *mshell, char *text, char *opwd, char *pwd)
{
	char	*str;

	if (!ft_strncmp(text, "OLDPWD=", 7))
	{
		str = ft_strjoin("OLDPWD=", opwd);
		if (!str)
			free_and_exit(mshell, 1);
	}
	else if (!ft_strncmp(text, "PWD=", 4))
	{
		str = ft_strjoin("PWD=", pwd);
		if (!str)
			free_and_exit(mshell, 1);
	}
	else
	{
		str = ft_strdup(text);
		if (!str)
			free_and_exit(mshell, 1);
	}
	return (str);
}

t_status	update_env(t_minishell *mshell, char *oldpwd, char *pwd)
{
	t_lst	*curr;
	t_lst	*new_env;
	t_lst	*tmp;

	new_env = malloc(sizeof(t_lst));
	tmp = new_env;
	if (!new_env)
		return (FAIL);
	curr = mshell->env;
	while (curr->next != mshell->env)
	{
		new_env->text = get_text(mshell, curr->text, oldpwd, pwd);
		new_env->next = malloc(sizeof(t_lst));
		if (!new_env->next)
			return (FAIL);
		curr = curr->next;
		new_env = new_env->next;
	}
	new_env->text = get_text(mshell, curr->text, oldpwd, pwd);
	if (!pwd_exist("OLDPWD=", mshell->env))
	{
		new_env->next = malloc(sizeof(t_lst));
		new_env->text = ft_strjoin("OLDPWD=", oldpwd);
	}
	if (!pwd_exist("PWD=", mshell->env))
	{
		new_env->next = malloc(sizeof(t_lst));
		new_env->text = ft_strjoin("PWD=", pwd);
	}
	new_env->next = tmp;
	mshell->env = new_env;
	return (SUCCESS);
}

void	print_cd_error(char *param)
{
	print_error(param);
	print_error(": ");
	print_error("too many arguments\n");
}

int	cd_minishell(t_minishell *mshell, char **params)
{
	int		res;
	int		arg_len;
	char	oldpwd[PATH_MAX];
	char	pwd[PATH_MAX];
	char	*path;

	arg_len = count_arg(params);
	if (arg_len == 1 || arg_len == 2)
	{
		if (arg_len == 1)
			path = getpath(mshell->env, "HOME=");
		else
			path = params[1];
		if (!getcwd(oldpwd, PATH_MAX))
			free_and_exit(mshell, 1);
		res = chdir(path);
		if (res == -1)
			return (perror(path), 1);
		if (!getcwd(pwd, PATH_MAX))
			free_and_exit(mshell, 1);
		if (!update_env(mshell, oldpwd, pwd))
			free_and_exit(mshell, 1);
		return (res);
	}
	return (print_cd_error(params[0]), 1);
}

#endif
