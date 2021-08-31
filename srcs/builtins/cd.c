/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 02:56:50 by melaena           #+#    #+#             */
/*   Updated: 2021/08/31 03:06:16 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_cd(char **args, t_dict *env)
{
	int		size;
	char	*path;
	size = get_args_size(args);

	if (size > 2)
	{
		ft_putstr_fd("minishel: cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	else if (size == 1)
		path = dict_get_value(env, "HOME");
	else if (size == 2)
		path = args[1];
	chdir(path);
	return (0);
}