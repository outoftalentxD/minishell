/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 14:26:55 by melaena           #+#    #+#             */
/*   Updated: 2021/09/12 23:14:27 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sect_set_type(t_sect *elem, int type)
{
	if (elem)
	{
		elem->type = type;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	sect_set_cmd_type(t_sect *elem, int type)
{
	if (elem)
	{
		elem->cmd_type = type;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	ft_free_args(char **args)
{
	int	i;

	i = -1;
	if (!args)
		return (EXIT_FAILURE);
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

int	get_next_char_pos(char *line, int start, int c)
{
	start++;
	while (line[start] && line[start] != c)
		start++;
	return (start);
}
