/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 16:16:25 by melaena           #+#    #+#             */
/*   Updated: 2021/08/31 16:00:19 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_command(char **args)
{
	char	*command;
	
	if (!ft_strcmp(args[0], "echo"))
		bi_echo(args);
	else if (!ft_strcmp(args[0], "pwd"))
		bi_pwd();
	else if (!ft_strcmp(args[0], "env"))
		bi_env(g_env);
	else if (!ft_strcmp(args[0], "export"))
		bi_export(args, g_env);
	else if (!ft_strcmp(args[0], "cd"))
		bi_cd(args, g_env);
	else if (!ft_strcmp(args[0], "unset"))
		bi_unset(args, &g_env);
	else
	{
		ft_putstr_fd(args[0], STDOUT_FILENO);
		ft_putstr_fd(": command not found\n", STDOUT_FILENO);
		return (-1);
	}
	return (0);
}