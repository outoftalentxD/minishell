/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 03:09:21 by melaena           #+#    #+#             */
/*   Updated: 2021/09/03 18:20:05 by melaena          ###   ########.fr       */
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

t_mshell	*init_mshell(char **env)
{
	t_mshell	*shell;

	shell = ft_calloc(1, sizeof(t_mshell));
	if (!shell)
		return (0);
	shell->env = init_env(env);
	shell->envp = env;
	shell->oldpwd = 0;
	shell->line = 0;
	return (shell);
}

t_sect	*init_sections(char **args)
{
	int		i;
	t_sect	*sect;
	
	i = 0;
	sect = 0;
	while (args[i])
	{
		sect_add_elem(&sect, sect_init_elem(args[i]));
		i++;
	}
	return (sect);
}
