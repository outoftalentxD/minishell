#include "minishell.h"

int	process_eof(char *line)
{
	printf("exit\n");
	free_mshell();
	free(line);
	exit(0);
}

void	free_sect(t_sect *elem)
{
	t_sect	*temp;

	while (elem)
	{
		temp = elem;
		if (elem->content)
			free(elem->content);
		if (elem->fd)
			free(elem->fd);
		elem = elem->next;
		free(temp);
	}
}

void	free_env(t_dict *env)
{
	t_dict	*temp;

	while (env)
	{
		temp = env;
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		env = env->next;
		free(temp);
	}
}

void	free_mshell(void)
{
	free(g_mshell->oldpwd);
	if (g_mshell->signal)
		free(g_mshell->signal);
	free_env(g_mshell->env);
	ft_free_args(g_mshell->envp);
}
