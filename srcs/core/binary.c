/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 23:44:35 by melaena           #+#    #+#             */
/*   Updated: 2021/09/12 23:10:59 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	throw_error_binary(char *path, int code)
{
	char	*error;
	int		ret;

	if (code == BIN_NO_FILE_OR_DIR_ERROR)
		error = ": No such file or directory: ";
	if (code == BIN_COMMAND_NOT_FOUND)
		error = ": command not found";
	if (code == BIN_IS_DIR_ERROR)
		error = ": Is a directory";
	if (code == BIN_COMMAND_NOT_FOUND || code == BIN_NO_FILE_OR_DIR_ERROR)
		ret = 127;
	else if (code == BIN_IS_DIR_ERROR)
		ret = 126;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putendl_fd(error, STDERR_FILENO);
	return (ret);
}

static int	is_right_path(char *path)
{
	int		fd;
	DIR		*dir;
	int		code;

	fd = open(path, O_WRONLY);
	dir = opendir(path);
	code = EXIT_SUCCESS;
	if (fd < 0 && dir)
		code = throw_error_binary(path, BIN_IS_DIR_ERROR);
	else if (fd >= 0 && !dir)
		code = throw_error_binary(path, BIN_PERMISSION_DENIED_ERROR);
	close(fd);
	if (dir)
		closedir(dir);
	return (code);
}

static int	bin_find_in_dir(char *name, char *path)
{
	struct dirent	*elem;
	DIR				*dir;

	dir = opendir(path);
	if (!dir)
		return (0);
	elem = readdir(dir);
	while (elem)
	{
		if (!ft_strcmp(elem->d_name, name))
		{
			closedir(dir);
			return (1);
		}
		elem = readdir(dir);
	}
	closedir(dir);
	return (0);
}

static char	*bin_find_in_path(char *name, t_dict *env)
{
	char	*value;
	char	**paths;
	int		i;

	value = dict_get_value(env, "PATH");
	if (!value)
		return (0);
	paths = ft_split(value, ':');
	i = 0;
	while (paths[i])
	{
		if (bin_find_in_dir(name, paths[i]))
			return (bin_form_path(name, paths[i]));
		i++;
	}
	ft_free_args(paths);
	return (0);
}

int	exec_binary(char **args, char **envp)
{
	char	*path;
	int		code;

	if (ft_strchr(args[0], '/'))
	{
		code = is_right_path(args[0]);
		if (code)
			return (code);
		if (execve(args[0], args, envp))
		{
			perror("minishell");
			return (BIN_NO_FILE_OR_DIR_ERROR);
		}
	}
	else
	{
		path = bin_find_in_path(args[0], g_mshell->env);
		if (!path)
			return (throw_error_binary(args[0], BIN_COMMAND_NOT_FOUND));
		execve(path, args, envp);
	}
	return (EXIT_SUCCESS);
}
