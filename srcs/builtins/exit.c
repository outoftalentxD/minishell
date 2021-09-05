/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 21:37:13 by melaena           #+#    #+#             */
/*   Updated: 2021/09/05 18:44:53 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	throw_error_exit(char *arg, int code)
{
	if (code == EXIT_TOO_MANY_ARGS_ERROR)
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
	else if (code == EXIT_NOT_NUM_ARG_ERROR)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit(2);
	}
	set_exit_status(127);
	return (code);
}

int	bi_exit(char **args)
{
	int		size;
	int		code;
	int		i;

	i = 0;
	code = 0;
	size = get_args_size(args);
	if (size > 1)
	{
		while (args[1][i])
		{
			if (!ft_isdigit(args[1][i]))
				return (throw_error_exit(args[1], EXIT_NOT_NUM_ARG_ERROR));
			i++;
		}
		code = ft_atoi(args[1]);
	}
	if (size > 2)
		return (throw_error_exit(0, EXIT_TOO_MANY_ARGS_ERROR));
	exit(code);
	return (EXIT_SUCCESS);
}
