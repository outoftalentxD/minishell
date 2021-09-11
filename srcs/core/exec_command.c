/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 14:28:36 by melaena           #+#    #+#             */
/*   Updated: 2021/09/11 15:31:29 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *arg)
{
	if (!arg)
		return (0);
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

static int	exec_builtin(char **args)
{
	int	code;

	if (!ft_strcmp(args[0], "echo"))
		code = bi_echo(args);
	else if (!ft_strcmp(args[0], "pwd"))
		code = bi_pwd(args);
	else if (!ft_strcmp(args[0], "env"))
		code = bi_env(g_mshell->env, args);
	else if (!ft_strcmp(args[0], "export"))
		code = bi_export(args, g_mshell->env);
	else if (!ft_strcmp(args[0], "cd"))
		code = bi_cd(args, g_mshell->env);
	else if (!ft_strcmp(args[0], "unset"))
		code = bi_unset(args, &g_mshell->env);
	else if (!ft_strcmp(args[0], "exit"))
		code = bi_exit(args);
	return (code);
}

int	exec_command(char **args)
{
	int		code;

	if (is_builtin(args[0]))
		code = exec_builtin(args);
	else
		code = exec_binary(args, g_mshell->envp);
	return (code);
}
