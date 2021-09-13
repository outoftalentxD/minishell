/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 02:56:50 by melaena           #+#    #+#             */
/*   Updated: 2021/09/13 15:16:36 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	throw_error_cd(char *path, int code)
{
	char	*error;

	if (code == CD_TOO_MANY_ARGS_ERROR)
		ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
	else if (code == CD_WORNG_PATH_ERROR)
	{
		error = strerror(errno);
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(error, STDERR_FILENO);
		if (path)
		{
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putendl_fd(path, STDERR_FILENO);
		}
	}
	return (EXIT_FAILURE);
}

static int	update_pwd(t_dict *env)
{
	t_dict	*elem;
	char	*path;
	char	buf[2048];

	elem = dict_get_elem(env, "PWD");
	path = getcwd(buf, 2048);
	if (!elem)
		dict_add_elem(&env, dict_init_elem(ft_strdup("PWD"), ft_strdup(path)));
	else
		dict_change_value_dup(elem, path);
	return (EXIT_SUCCESS);
}

static int	update_oldpwd(char *path, t_dict *env)
{
	t_dict	*elem;

	elem = dict_get_elem(env, "OLDPWD");
	if (!elem)
		dict_add_elem(&env, dict_init_elem(ft_strdup("OLDPWD"),
				ft_strdup(path)));
	else
		dict_change_value_dup(elem, path);
	if (g_mshell->oldpwd)
	{
		free(g_mshell->oldpwd);
		g_mshell->oldpwd = ft_strdup(path);
	}
	else
		g_mshell->oldpwd = ft_strdup(path);
	return (EXIT_SUCCESS);
}

int	bi_cd(char **args, t_dict *env)
{
	int		size;
	char	*path;
	char	buf[2048];
	char	*pwd;

	path = NULL;
	size = get_args_size(args);
	if (size > 2)
		return (throw_error_cd(0, CD_TOO_MANY_ARGS_ERROR));
	else if (size == 1)
		path = dict_get_value(env, "HOME");
	else if (size == 2)
		path = args[1];
	if (path)
	{
		pwd = getcwd(buf, 2048);
		if (chdir(path))
			return (throw_error_cd(path, CD_WORNG_PATH_ERROR));
		update_oldpwd(pwd, env);
		update_pwd(env);
	}
	return (EXIT_SUCCESS);
}
