#include <minishell.h>

static void	error_malloc(void)
{
	print_error("Malloc error\n");
	return ;
}

static int	count_arg(char **params)
{
	int	count;

	count = 0;
	while (params[count])
		count++;
	return (count);
}

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

int	cd_minishell(t_minishell *data, char **params)
{
	int	res;

	if (count_arg(params) == 1)
	{
		res = chdir(getenv("HOME"));
		if (res == 0)
			update_pwd(data);
		if (res == -1)
			res *= -1;
		if (res == 1)
			perror(getenv("HOME"));
		return (res);
	}
	else if (count_arg(params) == 2)
	{
		res = chdir(params[1]);
		if (res == 0)
			update_pwd(data);
		if (res == -1)
			res *= -1;
		if (res == 1)
			perror(params[1]);
		return (res);
	}
	return (1);
}
