/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 23:44:35 by melaena           #+#    #+#             */
/*   Updated: 2021/09/02 18:35:36 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int throw_error_binary(char *path, int code)
{
	char	*error;

	if (code == BIN_NO_FILE_OR_DIR_ERROR)
		error = ": No such file or directory: ";
	if (code == BIN_COMMAND_NOT_FOUND)
		error = ": command not found";
	if (code == BIN_IS_DIR_ERROR)
		error = ": Is a directory";
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putendl_fd(error, STDERR_FILENO);
	return (BIN_ERROR_CODE);
}

static int is_right_path(char *path, int opt)
{
	int		fd;
	DIR		*dir;
	int		code;

	fd = open(path, O_WRONLY);
	dir = opendir(path);
	code = 0;
	if (fd == -1 || !dir)
		code = BIN_ERROR_CODE;
	if (opt == 'd')
	{
		if (fd == -1 && !dir)
			throw_error_binary(path, BIN_NO_FILE_OR_DIR_ERROR);
		else if (fd != -1 && !dir)
			throw_error_binary(path, BIN_PERMISSION_DENIED_ERROR);
		else if (fd == -1 && dir)
			throw_error_binary(path, BIN_IS_DIR_ERROR);
	}
	else if (opt == 'c')
	{
		if (fd == -1)
			throw_error_binary(path, BIN_COMMAND_NOT_FOUND);
	}
	close(fd);
	closedir(dir);
	return (code);
}
static char	*bin_form_path(char *name, char *path)
{
	char	*temp;
	char	*ret;

	temp = ft_strjoin(path, "/");
	ret = ft_strjoin(temp, name);
	free(temp);
	return (ret);
}

static int		bin_find_in_dir(char *name, char *path)
{
	struct dirent	*elem;
	DIR				*dir;
	int				i;

	dir = opendir(path);
	if (!dir)
		return (0);
	while ((elem = readdir(dir)))
	{
		if (!ft_strcmp(elem->d_name, name))
			return (1);
	}
	return (0);
}

static char	*bin_find_in_path(char *name, t_dict *env)
{
	char	*value;
	char	**paths;
	DIR		*dir;
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
	return (0);
}

int exec_binary(char **args, char **envp)
{
	char	*path;
	char	*name;
	char	**argv;
	char	*command;

	name = args[0];
	if (ft_strchr(args[0], '/'))
	{
		// if (is_right_path(path, 'd'))
			// return (BIN_ERROR_CODE);
		if (execve(name, args, envp))
		{
			perror("minishell");
			return (BIN_ERROR_CODE);
		}
	}
	else
	{
		path = bin_find_in_path(name, g_mshell->env);
		if (!path)
			return (throw_error_binary(name, BIN_COMMAND_NOT_FOUND));
		execve(path, args, envp);
	}
	return (0);
}