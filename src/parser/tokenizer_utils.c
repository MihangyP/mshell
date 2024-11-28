#include <minishell.h>

int	token_new_elem(t_token **new, char *str, int type)
{
	if (!str)
		return (0);
	(*new) = malloc(sizeof(t_token));
	if (*new == NULL)
	{
		free(str);
		return (0);
	}
	(*new)->text = str;
	(*new)->id = type;
	(*new)->next = NULL;
	(*new)->prev = NULL;
	return (1);
}

void	add_first(t_token **list, t_token *new)
{
	(*list) = new;
	(*list)->prev = *list;
	(*list)->next = *list;
}

int	append_token(t_token **list, char *str, int type)
{
	t_token	*new;

	if (!token_new_elem(&new, str, type))
		return (0);
	if (!(*list))
		add_first(list, new);
	else
	{
		new->prev = (*list)->prev;
		new->next = (*list);
		(*list)->prev->next = new;
		(*list)->prev = new;
	}
	return (1);
}

void	print_token(t_token *token)
{
	t_token	*curr;

	if (token == NULL)
		return ;
	curr = token;
	while (curr->next != token)
	{
		printf("text: %s, id: %d\n", curr->text, curr->id);	
		curr = curr->next;
	}
	printf("text: %s, id: %d\n", curr->text, curr->id);
}
