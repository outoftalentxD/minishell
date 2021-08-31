/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 15:58:09 by melaena           #+#    #+#             */
/*   Updated: 2021/08/30 16:23:04 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_pwd(void)
{
	char cwd[2048];

	if (getcwd(cwd, 2048))
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (0);
	}
	else
		return (-1);
}
