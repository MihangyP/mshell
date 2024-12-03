#include <minishell.h>

size_t	len_cmd(t_cmd *list)
{
	t_cmd	*tmp;
	size_t	i;

	if ((list))
	{
		tmp = list;
		i = 1;
		while (tmp->next != list)
		{
			++i;
			tmp = tmp->next;
		}
		return (i);
	}
	return (0);
}

void	wait_all(t_minishell *mshell)
{
	int		status;
	int		pid;
	int		len;
	t_cmd	*tmp;

	tmp = mshell->cmd;
	len = len_cmd(tmp);
	while (len--)
	{
		pid = waitpid(0, &status, 0);
		if (pid == g_pid)
		{
			if (WIFEXITED(status))
				mshell->exit_code = WEXITSTATUS(status);
		}
		if (tmp->out >= 0)
			close(tmp->out);
		if (tmp->in >= 0)
			close(tmp->in);
		tmp = tmp->next;
	}
}
