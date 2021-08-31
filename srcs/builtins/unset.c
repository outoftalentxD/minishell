/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:04:59 by melaena           #+#    #+#             */
/*   Updated: 2021/08/31 16:02:34 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	throw_error_unset(char *arg, int code)
{
	char	*error;
	
	if (code == UNSET_FEW_ARGS_ERROR)
		error = ": not enough arguments";
	if (code == UNSET_KEY_CONTENT_ERROR)
		error = ": invalid parameter name";
	ft_putstr_fd("unset: ", STDERR_FILENO);
	if (code != UNSET_FEW_ARGS_ERROR)
		ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(error, STDERR_FILENO);
	return (0);
}

static int env_key_is_valid(char *key)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if (!ft_isenvkey(key[i]))
			return (UNSET_KEY_CONTENT_ERROR);
		i++;
	}
	return (0);
}

int	bi_unset(char **args, t_dict **env)
{
	int		size;
	char	*key;
	int		i;
	int		code;

	size = get_args_size(args);
	if (size < 2)
		return (throw_error_unset(args[i], UNSET_FEW_ARGS_ERROR));
	else
	{
		i = 1;
		while (args[i])
		{
			code = env_key_is_valid(args[i]);
			if (code)
				return (throw_error_unset(args[i], code));
			dict_del_by_key(env, args[i]);
			if (!(env))
				return (0);
			i++;
		}
	}
	return (0);
}