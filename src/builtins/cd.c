#include <minishell.h>

#if 0
void	update_oldpwd(t_minishell *mshell)
{
	char	pwd[PATH_MAX];
	t_lst	*tmp;

	if (!getcwd(pwd, PATH_MAX))
		strerror(errno);
	else
	{
		tmp = mshell->env;
		while (tmp->next != mshell->env)
		{
			if (!ft_strncmp(tmp->text, "OLDPWD=", 7))
			{
				export(ft_strjoin("OLDPWD=", pwd), &mshell->env);							
				break ;
			}
			tmp = tmp->next;
		}
		export("OLDPWD", &mshell->env);
	}
}
#endif
#if 1
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
		{
			printf("Malloc error\n");
			exit(1);
		}
		export(test, &mshell->env);
	}
	free(test);
}
#endif

#if 0
void	update_pwd(t_minishell *mshell)
{
	 char	tmp[PATH_MAX];

	 if (!getcwd(tmp, PATH_MAX))
	 {
		strerror(errno);
	 	return ;
	 }
	 export(ft_strjoin("PWD=", tmp), &mshell->env);
}
#endif
#if 1

void	update_pwd(t_minishell *mshell)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	//update_oldpwd(mshell);
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		strerror(errno);
		return ;
	}
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
	{
		printf("Malloc error\n");
		exit(1);
	}
	export(pwd, &mshell->env);
	free(pwd);
}

#endif

int	cd_minishell(t_minishell *mshell, char **params)
{
	int	status;

	if (params[0] && params[1] && !params[2])
	{
		status = chdir(params[1]);
		if (status == -1)
			strerror(errno);
		else if (!status)
		{
			update_oldpwd(mshell);
			update_pwd(mshell);
		}
		return (status);
	}
	return (1);
}
