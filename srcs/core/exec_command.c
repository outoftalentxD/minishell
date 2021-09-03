/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 16:16:25 by melaena           #+#    #+#             */
/*   Updated: 2021/09/03 21:07:58 by melaena          ###   ########.fr       */
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

static int	exec_builtin(char **args)
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
		bi_exit(args);
	return (0);
}

int	exec_command(char **args)
{
	char	*command;
	pid_t	pid;
	int		code;

	if (is_builtin(args[0]))
		exec_builtin(args);
	else
	{
		pid = fork();
		if (pid == -1)
			perror("fork: ");
		else if (pid == 0)
		{
			code = exec_binary(args, g_mshell->envp);
			exit(code);
		}
		else
			wait(0);
	}
	return (0);
}
