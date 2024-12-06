#include <minishell.h>

void	redirect_in_out(t_minishell *mshell, t_cmd *cmd, int *pip)
{
	close(pip[0]);
	if (cmd->in >= 0)
	{
		dup2(cmd->in, 0);
		close(cmd->in);
	}
	if (cmd->out >= 0)
	{
		dup2(cmd->out, 1);
		close(cmd->out);
	}
	else if (cmd->next != mshell->cmd)
		dup2(pip[1], 1);
	close(pip[1]);
}

void	child_process(t_minishell *mshell, t_cmd *cmd, int *pip)
{
	char	*path;
	char	**env;

	path = NULL;
	if (cmd->skip_cmd)
		mshell->exit_code = 1;
	else if (is_builtin(cmd->cmd_param[0]))
		built(pip, cmd, mshell);
	else if (cmd_exist(&path, mshell, cmd->cmd_param[0]))
	{
		redirect_in_out(mshell, cmd, pip);
		env = lst_to_arr(mshell->env);
		if (!env)
		{
			free_minishell(mshell);
			exit(1);
		}
		rl_clear_history();
		signals2();
		execve(path, cmd->cmd_param, env);
		free(env);
	}
	if (path)
		free(path);
	free_and_exit(mshell, mshell->exit_code);
}

void	parent_process(t_minishell *mshell, t_cmd *cmd, int *pip)
{
	close(pip[1]);
	if (cmd->in >= 0)
		close(cmd->in);
	if (cmd->in == -2)
		cmd->in = pip[0];
	if (cmd->next != mshell->cmd && cmd->next->in == -2)
		cmd->next->in = pip[0];
	else
		close(pip[0]);
}
