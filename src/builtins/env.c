#include <minishell.h>

int	env_minishell(t_lst *env)
{
	t_lst	*curr;

	curr = env;
	if (!curr)
		return (0);
	while (curr->next != env)
	{
		if (ft_strchr(curr->text, '='))
			printf("%s\n", curr->text);
		curr = curr->next;
	}
	if (ft_strchr(curr->text, '='))
		printf("%s\n", curr->text);
	return (0);
}
