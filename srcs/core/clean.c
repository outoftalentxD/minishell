#include "minishell.h"

void free_sect(t_sect *elem)
{
	t_sect *temp;
	while(elem)
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

void free_env(t_dict *env)
{
	t_dict *temp;

	while(env)
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

void free_mshell()
{
	int i;

	i = 0;
	free(g_mshell->oldpwd);
	if (g_mshell->fd)
		free(g_mshell->fd);
	if (g_mshell->signal)
		free(g_mshell->signal);
	free_env(g_mshell->env);
	free_sect(g_mshell->sect);
}