/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:32:33 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/12 11:03:58 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	count_arg(char **params)
{
	int	count;

	count = 0;
	while (params[count])
		count++;
	return (count);
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
	new_env->next = tmp;
	mshell->env = new_env;
	return (SUCCESS);
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
			path = getenv("HOME");
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
	else
	{
		print_error(params[0]);
		print_error(": ");
		print_error("too many arguments\n");
	}
	return (1);
}
