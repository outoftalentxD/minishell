/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbulwer <kbulwer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 20:39:45 by melaena           #+#    #+#             */
/*   Updated: 2021/09/07 18:02:46 by kbulwer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sect	*get_next_cmd(t_sect *elem)
{
	elem = elem->next;
	while (elem)
	{
		if (elem->type == SECT_TYPE_CMD)
			return (elem);
		elem = elem->next;
	}
	return (elem);
}

t_sect	*get_prev_cmd(t_sect *elem)
{
	elem = elem->prev;
	while (elem)
	{
		if (elem->type == SECT_TYPE_CMD)
			return (elem);
		elem = elem->prev;
	}
	return (elem);
}

int	close_pipeline(t_sect *elem)
{
	t_sect	*temp;

	while (elem->prev)
		elem = elem->prev;
	while (elem)
	{
		if (elem->fd->in != STDIN_FILENO)
			close(elem->fd->in);
		if (elem->fd->out != STDOUT_FILENO)
			close(elem->fd->out);
		elem = elem->next;
	}
	return (EXIT_SUCCESS);
}

int	open_pipeline(t_sect *elem)
{
	int		fd[2];
	t_sect	*cmd_prev;
	t_sect	*cmd_next;

	if (elem->type != SECT_TYPE_PIPE)
		return (EXIT_FAILURE);
	cmd_next = get_next_cmd(elem);
	cmd_prev = get_prev_cmd(elem);
	pipe(fd);
	cmd_prev->fd->out = fd[1];
	cmd_next->fd->in = fd[0];
	return (EXIT_SUCCESS);
}
