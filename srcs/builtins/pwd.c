/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 15:58:09 by melaena           #+#    #+#             */
/*   Updated: 2021/09/13 15:47:54 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_pwd(char **args)
{
	char	cwd[2048];
	int		size;

	size = get_args_size(args);
	if (getcwd(cwd, 2048))
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (set_exit_status(EXIT_SUCCESS));
	}
	else
		return (set_exit_status(EXIT_FAILURE));
}
