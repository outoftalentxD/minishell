/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 03:09:21 by melaena           #+#    #+#             */
/*   Updated: 2021/08/28 15:35:41 by melaena          ###   ########.fr       */
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
				break;
			len++;
		}
		key = ft_substr(*env, 0, len);
		value = ft_substr(*env, len + 1, ft_strlen(*env));
		dict_add_elem(&denv, dict_init_elem(key, value));		
		env++;
	}
	return (denv);
}

t_mshell *init_mshell(char **env)
{
	t_mshell *shell;

	shell = ft_calloc(1, sizeof(t_mshell));
	if (!shell)
		return (0);
	return (shell);
}