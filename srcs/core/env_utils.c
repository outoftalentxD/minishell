/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 11:22:36 by melaena           #+#    #+#             */
/*   Updated: 2021/09/12 23:25:26 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	inc_shlvl(t_dict **env)
{
	t_dict	*elem;
	char	*key;
	char	*value;
	int		lvl;

	elem = dict_get_elem(*env, "SHLVL");
	if (!elem)
	{
		key = ft_strdup("SHLVL");
		value = ft_strdup("1");
		dict_add_elem(env, dict_init_elem(key, value));
		return (EXIT_SUCCESS);
	}
	lvl = ft_atoi(elem->value);
	if (lvl == -1)
		lvl = 0;
	dict_change_value(elem, ft_itoa(lvl + 1));
	return (EXIT_SUCCESS);
}

static char	*form_env_arg(char *key, char *value)
{
	char	*temp;
	char	*arg;

	temp = ft_strjoin(key, "=");
	arg = ft_strjoin(temp, value);
	free(temp);
	return (arg);
}

int	update_mshell_env(void)
{
	if (g_mshell->envp)
		ft_free_args(g_mshell->envp);
	g_mshell->envp = form_env(g_mshell->env);
	return (EXIT_SUCCESS);
}

char	**form_env(t_dict *elem)
{
	char	**env;
	int		size;
	int		i;

	size = dict_get_size(elem);
	if (!size)
		return (0);
	env = ft_calloc(size + 1, sizeof(char *));
	if (!env)
		return (0);
	i = 0;
	while (elem)
	{
		env[i] = form_env_arg(elem->key, elem->value);
		i++;
		elem = elem->next;
	}
	return (env);
}
