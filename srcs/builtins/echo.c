/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 15:07:46 by melaena           #+#    #+#             */
/*   Updated: 2021/08/31 16:14:42 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_args_size(char **args)
{
	int	size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

int	bi_echo(char **args)
{
	int	i;
	int	n_opt;
	int	size;

	n_opt = 0;
	size = get_args_size(args);
	if (size > 1)
	{
		while (args[n_opt + 1] && !ft_strcmp(args[n_opt + 1], "-n"))
			n_opt++;
		i = n_opt + 1;
		while (args[i])
		{
			ft_putstr_fd(args[i], STDOUT_FILENO);
			if (args[i + 1])
				ft_putstr_fd(" ", STDOUT_FILENO);
			i++;
		}
	}
	if (!n_opt)
		ft_putstr_fd("\n", STDOUT_FILENO);
}
