/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 14:26:55 by melaena           #+#    #+#             */
/*   Updated: 2021/08/31 16:02:31 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_free_args(char **args)
{
	int i;

	i = -1;
	while (args[++i])
		free(args[i]);
	free(args);
	return (0);
}

int	ft_isenvkey(int c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	else
		return (0);
}
