/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 03:09:21 by melaena           #+#    #+#             */
/*   Updated: 2021/09/05 02:40:25 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dict	*init_env(char **env)
{
	t_dict	*denv;
	char	*key;
	char	*value;
	int		len;

	denv = 0;
	while (*env)
	{	
		len = 0;
		while ((*env)[len])
		{
			if ((*env)[len] == '=')
				break ;
			len++;
		}
		key = ft_substr(*env, 0, len);
		value = ft_substr(*env, len + 1, ft_strlen(*env));
		dict_add_elem(&denv, dict_init_elem(key, value));
		env++;
	}
	return (denv);
}

t_sig		*init_signal(void)
{
	t_sig	*signal;

	signal = ft_calloc(1, sizeof(t_sig));
	if (!signal)
		return (0);
	signal->sigint = 1;
	return (signal);
}

t_mshell	*init_mshell(char **env)
{
	t_mshell	*shell;

	shell = ft_calloc(1, sizeof(t_mshell));
	if (!shell)
		return (0);
	shell->env = init_env(env);
	shell->envp = env;
	shell->oldpwd = 0;
	shell->sect = 0;
	shell->signal = init_signal();
	return (shell);
}
