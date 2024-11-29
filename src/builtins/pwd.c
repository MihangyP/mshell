#include <minishell.h>

int	pwd_minishell(void)
{
	char	buf[PATH_MAX];

	if (getcwd(buf, PATH_MAX))
	{
		printf("%s\n", buf);
		return (0);
	}
	perror("pwd");
	return (1);
}
