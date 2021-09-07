/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbulwer <kbulwer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 16:28:42 by melaena           #+#    #+#             */
/*   Updated: 2021/09/07 18:10:19 by kbulwer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	throw_error_env(int code)
{
	if (code == ENV_TOO_MANY_ARGS_ERROR)
		ft_putendl_fd("env: too many arguments", STDERR_FILENO);
	return (set_exit_status(EXIT_FAILURE));
}

int	bi_env(t_dict *env, char **args)
{
	int	size;

	size = get_args_size(args);
	if (size > 1)
		return (throw_error_env(ENV_TOO_MANY_ARGS_ERROR));
	while (env)
	{
		ft_putstr_fd(env->key, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putendl_fd(env->value, STDOUT_FILENO);
		env = env->next;
	}
	return (set_exit_status(EXIT_SUCCESS));
}
