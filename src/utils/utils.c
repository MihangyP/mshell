#include <minishell.h>

int	is_space(const char c)
{
	return (c == 32 || (c > 8 && c < 14));
}

bool	is_empty(const char *str)
{
	while (*str && is_space(*str))
		++str;
	if (*str)
		return (false);
	return (true);
}

bool	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static void	ft_swap_str_tab(int i, int j, char **tab)
{
	char	*temp;

	temp = tab[i];
	tab[i] = tab[j];
	tab[j] = temp;
}

void	sort_array(char **arr, int len)
{
	int	i;
	int	j;
	int	diff;

	i = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			diff = ft_strncmp(arr[i], arr[j], __INT_MAX__);
			if (diff > 0)
			{
				ft_swap_str_tab(i, j, arr);
				continue ;
			}
			j++;
		}
		i++;
	}
}
