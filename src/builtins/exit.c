#include <minishell.h>

int	almost_atoi(char *str, int *err)
{
	unsigned long long	ret;
	int					i;
	int					j;
	int					pn;

	i = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	pn = 1;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			pn = -1;
	j = i;
	ret = 0;
	while ('0' <= str[i] && str[i] <= '9')
		ret = ret * 10 + (str[i++] - 48);
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] || i - j > 20 || ((pn == -1 && (ret - 1) > LONG_MAX) || \
		(pn == 1 && (ret > LONG_MAX))))
		*err = 1;
	return ((int)((ret * pn) % 256));
}

void	ft_exit(t_minishell *mshell, char **args)
{
	int	ret;
	int	err;

	ret = 0;
	err = 0;
	if (args[1])
	{
		ret = almost_atoi(args[1], &err);
		if (err)
		{
			print_error("exit: ");
			print_error(args[1]);
			print_error(": numeric argument required\n");
			free_minishell(mshell);
		}
	}
	if (args[1] && args[2])
	{
		print_error("exit: too many arguments\n");
		mshell->exit_code = 1;
		return ;
	}
	if (!args[1])
	{
		free_minishell(mshell);
		exit(ret);
	}
	free_minishell(mshell);
	exit(ret);
}
