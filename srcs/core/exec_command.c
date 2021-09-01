/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 16:16:25 by melaena           #+#    #+#             */
/*   Updated: 2021/09/01 21:43:10 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin(char *arg)
{
	if (!ft_strcmp(arg, "echo"))
		return (1);
	else if (!ft_strcmp(arg, "pwd"))
		return (1);
	else if (!ft_strcmp(arg, "env"))
		return (1);
	else if (!ft_strcmp(arg, "export"))
		return (1);
	else if (!ft_strcmp(arg, "cd"))
		return (1);
	else if (!ft_strcmp(arg, "unset"))
		return (1);
	else if (!ft_strcmp(arg, "exit"))
		return (1);
	else
		return (0);
}

static int exec_builtin(char **args)
{
	if (!ft_strcmp(args[0], "echo"))
		bi_echo(args);
	else if (!ft_strcmp(args[0], "pwd"))
		bi_pwd();
	else if (!ft_strcmp(args[0], "env"))
		bi_env(g_mshell->env);
	else if (!ft_strcmp(args[0], "export"))
		bi_export(args, g_mshell->env);
	else if (!ft_strcmp(args[0], "cd"))
		bi_cd(args, g_mshell->env);
	else if (!ft_strcmp(args[0], "unset"))
		bi_unset(args, &g_mshell->env);
	else if (!ft_strcmp(args[0], "exit"))
		bi_exit();
	return (0);
}

int	exec_command(char **args)
{
	char	*command;
	
	if (is_builtin(args[0]))
		exec_builtin(args);
	else
	{
		ft_putstr_fd(args[0], STDOUT_FILENO);
		ft_putstr_fd(": command not found\n", STDOUT_FILENO);
		return (-1);
	}
	return (0);
}
