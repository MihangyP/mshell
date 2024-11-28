#include <minishell.h>

int	check_new_line(char *str)
{
	int	i;

	i = 0;
	if (str[i] && str[i] == '-')
	{
		++i;
		while (str[i] && str[i] == 'n')
			i++;
		if (i == (int)ft_strlen(str))
			return (1);
	}
	return (0);
}

void	write_echo(int count, int i, bool new_line, char **args)
{
	while (args[i] && check_new_line(args[i]))
	{
		++i;
		new_line = false;
	}
	while (i < count)
	{
		write(1, args[i], ft_strlen(args[i]));
		if (i != count - 1)
			write(1, " ", 1);
		++i;
	}
	if (new_line)
		write(1, "\n", 1);
}

int	ft_echo(char **args)
{
	int		count;
	int		i;
	bool	new_line;

	count = 0;
	while (args[count])
		++count;
	i = 1;
	new_line = true;
	write_echo(count, i, new_line, args);
	return (0);
}
