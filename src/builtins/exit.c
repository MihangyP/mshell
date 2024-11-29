#include <minishell.h>

// To understand
static int	get_return_value(char *str, bool *err)
{
	unsigned long long	ret;
	int					i;
	int					j;
	int					pn;

	i = 0;
	while (is_space(str[i]))
		i++;
	pn = 1;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			pn = -1;
	j = i;
	ret = 0;
	while (ft_isdigit(str[i]))
		ret = ret * 10 + (str[i++] - 48);
	while (is_space(str[i]))
		i++;
	if (str[i] || i - j > 20 || ((pn == -1 && (ret - 1) > LONG_MAX) || \
		(pn == 1 && (ret > LONG_MAX))))
		*err = true;
	return ((int)((ret * pn) % 256));
}

void	exit_minishell(t_minishell *mshell, char **av)
{
	bool	err;
	int		return_value;

	if (!av[1])
	{
		free_minishell(mshell);
		exit(0);
	}
	if (av[2])
	{
		print_error("exit: too many arguments\n");
		mshell->exit_code = 1;
		return ;
	}
	err = false;
	return_value = get_return_value(av[1], &err);
	if (err)
	{
		print_error("exit: ");
		print_error(av[1]);
		print_error(": numeric argument required\n");
		free_minishell(mshell);
	}
	free_minishell(mshell);
	exit(return_value);
}
