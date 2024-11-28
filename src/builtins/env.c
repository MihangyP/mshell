#include <minishell.h>

int	ft_env(t_lst *env)
{
	t_lst	*temp;

	temp = env;
	if (!temp)
		return (0);
	if (ft_strchr(temp->text, '='))
		printf("%s\n", temp->text);
	temp = temp->next;
	while (temp != env)
	{
		if (ft_strchr(temp->text, '='))
			printf("%s\n", temp->text);
		temp = temp->next;
	}
	return (0);
}