/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 15:58:09 by melaena           #+#    #+#             */
/*   Updated: 2021/09/05 18:38:20 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	throw_error_pwd(int code)
{
	if (code == PWD_TOO_MANY_ARGS_ERROR)
	{
		set_exit_status(1);
		ft_putendl_fd("pwd: too many arguments", STDERR_FILENO);
	}
	return (code);
}

int	bi_pwd(char **args)
{
	char	cwd[2048];
	int		size;

	size = get_args_size(args);
	if (size > 1)
		return (throw_error_pwd(PWD_TOO_MANY_ARGS_ERROR));
	if (getcwd(cwd, 2048))
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (set_exit_status(EXIT_SUCCESS));
	}
	else
		return (set_exit_status(EXIT_FAILURE));
}
