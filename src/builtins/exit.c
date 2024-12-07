#include <minishell.h>

static int	get_exit_value(char *str, bool *err)
{
	int					i;
	int					neg;
	int					start_index;
	unsigned long long	num;

	i = 0;
	neg = 1;
	num = 0;
	while (is_space(str[i]))
		++i;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			neg = -1;
	start_index = i;
	while (ft_isdigit(str[i]))
		num = num * 10 + (str[i++] - 48);
	while (is_space(str[i]))
		++i;
	if (str[i] || i - start_index > 20 || ((neg == -1 && (num - 1) > LONG_MAX) || \
		(neg == 1 && (num > LONG_MAX))))
		*err = true;
	return ((int)((num * neg) % 256));
}

void	exit_minishell(t_minishell *mshell, char **av)
{
	bool	err;
	int		exit_value;

	if (!av[1])
		free_and_exit(mshell, mshell->exit_code);
	if (av[2])
	{
		print_error("exit: too many arguments\n");
		mshell->exit_code = 1;
		return ;
	}
	err = false;
	exit_value = get_exit_value(av[1], &err);
	if (err)
	{
		print_error("exit: ");
		print_error(av[1]);
		print_error(": numeric argument required\n");
		free_and_exit(mshell, 2);
	}
	free_and_exit(mshell, exit_value);
}
