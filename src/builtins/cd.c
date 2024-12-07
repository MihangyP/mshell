#include <minishell.h>

static int	count_arg(char **params)
{
	int	count;

	count = 0;
	while (params[count])
		count++;
	return (count);
}

#if 0
void	update_oldpwd(t_minishell *mshell)
{
	t_lst	*tmp;
	char	*test;
	int		len;

	tmp = mshell->env;
	test = NULL;
	len = len_list(tmp);
	while (len--)
	{
		if (ft_strncmp(tmp->text, "PWD=", 3) == 0)
			test = tmp->text;
		tmp = tmp->next;
	}
	if (!test)
		export("OLDPWD", &mshell->env);
	if (test)
	{
		test = ft_strjoin("OLD", test);
		if (!test)
			return (error_malloc());
		export(test, &mshell->env);
	}
	free(test);
}

void	update_pwd(t_minishell *mshell)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	update_oldpwd(mshell);
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		strerror(errno);
		return ;
	}
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		return (error_malloc());
	export(pwd, &mshell->env);
	free(pwd);
}
#endif

char	*get_text(t_minishell *mshell, char *text, char *opwd, char *pwd)
{
	char 	*str;

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
	new_env->next = tmp;
	mshell->env = new_env;
	return (SUCCESS);
}

int	cd_minishell(t_minishell *mshell, char **params)
{
	int	res;
	int	arg_len;
	char	oldpwd[PATH_MAX];
	char	pwd[PATH_MAX];
	char 	*path;

	arg_len = count_arg(params);
	if (arg_len == 1 || arg_len == 2)
	{
		if (arg_len == 1)
			path = getenv("HOME");
		else
			path = params[1];
		if (!getcwd(oldpwd, PATH_MAX))
			free_and_exit(mshell, 1);
		res = chdir(path);
		if (!getcwd(pwd, PATH_MAX) || res == -1)
			free_and_exit(mshell, 1);
		if (res == -1)
			free_and_exit(mshell, 1);
		if (!update_env(mshell, oldpwd, pwd))
			return (1);
		return (res);
	}
	return (1);
}
